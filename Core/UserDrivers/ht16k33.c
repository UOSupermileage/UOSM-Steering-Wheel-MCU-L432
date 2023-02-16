/*
 * sevensegment.c
 *
 *  Created on: 20.05.2022
 *      Author: lenni
 */

#include "ht16k33.h"

/*********************************************************************************
 *
 * 		Commands for display
 *
 **********************************************************************************/

typedef uint8_t i2c_address_t;

// Commands
#define HT16K33_ON              0x21  // 0=off 1=on
#define HT16K33_STANDBY         0x20  // bit xxxxxxx0

// bit pattern 1000 0xxy
// y    =  display on / off
// xx   =  00=off     01=2Hz     10=1Hz     11=0.5Hz
#define HT16K33_DISPLAYON       0x81
#define HT16K33_DISPLAYOFF      0x80
#define HT16K33_BLINKON0_5HZ    0x87
#define HT16K33_BLINKON1HZ      0x85
#define HT16K33_BLINKON2HZ      0x83
#define HT16K33_BLINKOFF        0x81

// bit pattern 1110 xxxx
// xxxx    =  0000 .. 1111 (0 - F)
#define HT16K33_BRIGHTNESS      0xE0

#define HT16K33_CACHE_SIZE 5

//
//  HEX codes 7 segment
//
//      01
//  20      02
//      40
//  10      04
//      08
//
const uint8_t charmap[] = {
		0x3F,   // 0
		0x06,   // 1
		0x5B,   // 2
		0x4F,   // 3
		0x66,   // 4
		0x6D,   // 5
		0x7D,   // 6
		0x07,   // 7
		0x7F,   // 8
		0x6F,   // 9
		0x77,   // A
		0x7C,   // B
		0x39,   // C
		0x5E,   // D
		0x79,   // E
		0x71,   // F
		0x00,   // space
		0x40,   // minus
		0x30,   // I
		0x38,   // L
};

/*********************************************************************************
 *
 * 		Display cache
 *
 **********************************************************************************/

typedef struct {
	SegDisplayIndex id;
	uint8_t cache[HT16K33_CACHE_SIZE]; 			//cache for performance
	uint8_t	digits;					//number of digits to display (0-4)
	uint8_t brightness;			//current brightness (0-15)
	i2c_address_t address;
} display_data_t;

static volatile display_data_t displays[HT16K33_N_DISPLAY] = {
		{
				DISPLAY_0,
				{},
				4,
				15,
				0x70
		},
		{
				DISPLAY_1,
				{},
				4,
				15,
				0x71
		}
};

/*********************************************************************************
 *
 * 		I2C Write Functions (PRIVATE)
 *
 **********************************************************************************/

/**
 * Sends complete cached data over i2c
 */
static void _refresh(SegDisplayIndex id) {

	uint8_t pData[2];

	for (uint8_t pos = 0; pos < 4; pos++) {
		pData[0] = pos * 2;
		pData[1] = displays[id].cache[pos];

		HAL_I2C_Master_Transmit(&HT16K33_I2C_PORT, displays[id].address << 1, pData, 2, HAL_MAX_DELAY);
	}
}

/**
 * Sends given command over i2c
 */
static void _writeCmd(SegDisplayIndex id, uint8_t cmd) {
	HAL_I2C_Master_Transmit(&HT16K33_I2C_PORT, displays[id].address << 1, &cmd, 1, HAL_MAX_DELAY);
}

/**
 * Sends value (mask) for specific position per i2c, if different from cached value
 */
static void _writePos(SegDisplayIndex id, uint8_t pos, uint8_t mask) {
	if (displays[id].cache[pos] == mask)
		return;

	uint8_t pData[2];
	pData[0] = pos * 2;
	pData[1] = mask;

	HAL_I2C_Master_Transmit(&HT16K33_I2C_PORT, displays[id].address << 1, pData, 2, HAL_MAX_DELAY);
	displays[id].cache[pos] = mask;	// update value in cache
}

/**
 * Update mask to display point at given location, before sending it per i2c
 */
static void _writePosPoint(SegDisplayIndex id, uint8_t pos, uint8_t mask, int point) {
	if (point)
		mask |= 0x80;
	else
		mask &= 0x7F;

	_writePos(id, pos, mask);
}

/*********************************************************************************
 *
 * 		Display Control Functions (PUBLIC)
 *
 **********************************************************************************/

void HT16K33_Init(SegDisplayIndex id) {
	HT16K33_Reset(id);
	HT16K33_DisplayOn(id);
}

void HT16K33_Reset(SegDisplayIndex id) {
	HT16K33_DisplayClear(id);
	HT16K33_ClearCache(id);
	HT16K33_SetBlinkRate(id, 0);
	HT16K33_SetDigits(id, 4);
	HT16K33_SetBrightness(id, 15);
}

void HT16K33_ClearCache(SegDisplayIndex id) {
	for (uint8_t i = 0; i < HT16K33_CACHE_SIZE; i++) {
		displays[id].cache[i] = SEG7_NONE;
	}
}

void HT16K33_Refresh(SegDisplayIndex id) {
	_refresh(id);
}

void HT16K33_DisplayOn(SegDisplayIndex id) {
	_writeCmd(id, HT16K33_ON);
	_writeCmd(id, HT16K33_DISPLAYON);

	HT16K33_SetBrightness(id, displays[id].brightness);
}

void HT16K33_DisplayOff(SegDisplayIndex id) {
	_writeCmd(id, HT16K33_DISPLAYOFF);
	_writeCmd(id, HT16K33_STANDBY);
}

void HT16K33_SetBlinkRate(SegDisplayIndex id, uint8_t value) {
	if (value > 0x03) {
		value = 0x00;
	}

	_writeCmd(id, HT16K33_BLINKOFF | (value << 1));
}

void HT16K33_SetBrightness(SegDisplayIndex id, uint8_t value) {
	if (value == displays[id].brightness)
		return;

	displays[id].brightness = (value < 0x0F) ? value : 0x0F;

	_writeCmd(id, HT16K33_BRIGHTNESS | displays[id].brightness);
}

void HT16K33_SetDigits(SegDisplayIndex id, uint8_t value) {
	displays[id].digits = (value > 4) ? 4 : value;
}

//#####  END: CONTROL-FUNCTIONS  #####
//####################################
//##### BEGIN: DISPLAY-FUNCTIONS #####

void HT16K33_DisplayClear(SegDisplayIndex id) {
	uint8_t arr[4] = { SEG7_SPACE, SEG7_SPACE, SEG7_SPACE, SEG7_SPACE };
	HT16K33_Display(id, arr);
	HT16K33_DisplayColon(id, 0);
}

int HT16K33_DisplayInt(SegDisplayIndex id, int n) {
	int inRange = ((-1000 < n) && (n < 10000));
	int neg = (n < 0);

	uint8_t arr[4], h, l;

	if (neg)
		n = -n;

	h = n / 100;
	l = n - h * 100;
	arr[0] = h / 10;
	arr[1] = h - arr[0] * 10;
	arr[2] = l / 10;
	arr[3] = l - arr[2] * 10;

	if (neg) {
		if (displays[id].digits >= 3) {
			arr[0] = SEG7_MINUS;
		} else {
			int i = 0;
			for (i = 0; i < (4 - displays[id].digits); i++) {
				if (arr[i] != 0) {
					break;
				}
				arr[i] = SEG7_SPACE;
			}
			arr[i - 1] = SEG7_MINUS;
		}
	}

	HT16K33_Display(id, arr);

	return inRange;
}

int HT16K33_DisplayTime(SegDisplayIndex id, uint8_t left, uint8_t right, int colon) {
	int inRange = ((left < 100) && (right < 100));
	uint8_t arr[4];

	arr[0] = left / 10;
	arr[1] = left - arr[0] * 10;

	arr[2] = right / 10;
	arr[3] = right - arr[2] * 10;

	HT16K33_Display(id, arr);
	HT16K33_DisplayColon(id, colon);

	return inRange;
}

void HT16K33_Display(SegDisplayIndex id, uint8_t *array) {
	for (uint8_t i = 0; i < (4 - displays[id].digits); i++) {
		if (array[i] != 0) {
			break;
		}
		array[i] = SEG7_SPACE;
	}

	_writePos(id, 0, charmap[array[0]]);
	_writePos(id, 1, charmap[array[1]]);
	_writePos(id, 3, charmap[array[2]]);
	_writePos(id, 4, charmap[array[3]]);
}

void HT16K33_DisplayPoint(SegDisplayIndex id, uint8_t *array, uint8_t point) {
	_writePosPoint(id, 0, charmap[array[0]], point == 0);
	_writePosPoint(id, 1, charmap[array[1]], point == 1);
	_writePosPoint(id, 3, charmap[array[2]], point == 2);
	_writePosPoint(id, 4, charmap[array[3]], point == 3);
}

void HT16K33_DisplayColon(SegDisplayIndex id, uint8_t on) {
	_writePos(id, 2, on ? 2 : 0);
}

void HT16K33_DisplayRaw(SegDisplayIndex id, uint8_t *array, int colon) {
	_writePos(id, 0, array[0]);
	_writePos(id, 1, array[1]);
	_writePos(id, 3, array[2]);
	_writePos(id, 4, array[3]);
	_writePos(id, 2, colon ? 255 : 0);
}

//##### END: DISPLAY-FUNCTIONS #####
