/*
 * ht16k33.h
 *
 *  Created on: May 18, 2022
 *  Author: Lennart Koepper
 */

#ifndef USERDRIVERS_HT16K33_H_
#define USERDRIVERS_HT16K33_H_

#include "stdint.h"

// !!! Adjust the following include according to your stm32 !!!
#include "stm32l4xx_hal.h" //WARNING MOVE THE STM32 HAL FILE TO THE CORRECT FILE PATH

extern I2C_HandleTypeDef hi2c1;

// !!! I2C Configuration !!!
#define HT16K33_I2C_PORT        hi2c1
#define HT16K33_I2C_ADDR        0x70

// displayable Characters
#define SEG7_0                0
#define SEG7_1                1
#define SEG7_2                2
#define SEG7_3                3
#define SEG7_4                4
#define SEG7_5                5
#define SEG7_6                6
#define SEG7_7                7
#define SEG7_8                8
#define SEG7_9                9
#define SEG7_A                10
#define SEG7_B                11
#define SEG7_C                12
#define SEG7_D                13
#define SEG7_E                14
#define SEG7_F                15
#define SEG7_SPACE            16
#define SEG7_MINUS            17
#define SEG7_I                18		// I & L, e.g. to write "FAIL"
#define SEG7_L                19
#define SEG7_NONE             99

void HT16K33_Init(void);		// initializes 7-segment-display
void HT16K33_Reset(void);		// resets 7-segment-display
void HT16K33_ClearCache(void);	// force clearing of the cache
void HT16K33_Refresh(void); 	// force writing of cache to display

void HT16K33_DisplayOn(void);	// enable display
void HT16K33_DisplayOff(void);	// disable display, fastest way to darken display

void HT16K33_SetBrightness(uint8_t value);		// 0 .. 15	  0 = off, 15 = max. brightness
void HT16K33_SetBlinkRate(uint8_t value);      // 0 .. 3     0 = off, 1 = 2Hz, 2 = 1Hz, 3 = 0,5Hz
void HT16K33_SetDigits(uint8_t value);			// 0 .. 4	  minimal number of digits shown

void HT16K33_DisplayClear(void);									// fills display with spaces
int  HT16K33_DisplayInt(int n);                   					// -999 .. 9999
int  HT16K33_DisplayTime(uint8_t left, uint8_t right, int colon);	// 00:00 .. 99:99, colon can be set to false (e.g. simulate blink)

void HT16K33_Display(uint8_t *array);                  	// displays 4 displayable Character values (stored in array)
void HT16K33_DisplayPoint(uint8_t *array, uint8_t point);  // displays 4 displayable Character values (stored in array), point = digit with . (0..3)
void HT16K33_DisplayColon(uint8_t on);                 	// 0 = off
void HT16K33_DisplayRaw(uint8_t *array, int colon);  		// control the 4 Characters and the colon

#endif /* USERDRIVERS_HT16K33_H_ */
