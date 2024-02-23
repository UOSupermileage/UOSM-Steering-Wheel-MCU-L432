/*
 * I2CDisplayDriver.c
 *
 *  Created on: Aug 6, 2022
 *      Author: saurav g
 */
#include "I2CDisplayDriver.h"
#include "ht16k33.h"


PUBLIC DisplayStatusID_t Seg_Display_Initialize(SegDisplayIndex id) {
    HT16K33_Init(id);
    return DISPLAY_STATUS_INITIALIZED;
}

/**
 * Takes speed in km / hour
 */
PUBLIC DisplayStatusID_t Seg_Display_Speed(SegDisplayIndex id, speed_t n, flag_status_t throttleTooHigh) {

	int inRange = (n >= 0 && n < 1000);

	if (!inRange) {
		return DISPLAY_ERROR_UNABLE_TO_DISPLAY_FAIL;
	}

	uint8_t arr[4], h, l;

	h = n / 100;
	l = n - h * 100;

	// Display the 4 digits
	arr[0] = h / 10;
	arr[1] = h - arr[0] * 10;
	arr[2] = l / 10;
	arr[3] = l - arr[2] * 10;

	// Replace most significant digit with E or space
	arr[0] = (throttleTooHigh == Set) ? SEG7_E : SEG7_SPACE;

	if (arr[1] == 0) {
		arr[1] = SEG7_SPACE;

		if (arr[2] == 0) {
			arr[2] = SEG7_SPACE;
		}
	}


	HT16K33_Display(id, arr);

	// Turn off the colon
	HT16K33_DisplayColon(id, 0);

	return DISPLAY_STATUS_OK;
}

PUBLIC DisplayStatusID_t Seg_Display_Voltage(SegDisplayIndex id, voltage_t voltage) {

	int n = voltage * 33 * 185 / 40960;

	int inRange = (n >= 0 && n < 1000);

		if (!inRange) {
			return DISPLAY_ERROR_UNABLE_TO_DISPLAY_FAIL;
		}

		uint8_t arr[4], h, l;

		h = n / 100;
		l = n - h * 100;

		// Display the 4 digits
		arr[0] = h / 10;
		arr[1] = h - arr[0] * 10;
		arr[2] = l / 10;
		arr[3] = l - arr[2] * 10;

		// Replace most significant digit with E or space
		arr[0] = SEG7_L;

		if (arr[1] == 0) {
			arr[1] = SEG7_SPACE;

			if (arr[2] == 0) {
				arr[2] = SEG7_SPACE;
			}
		}


		HT16K33_Display(id, arr);
		HT16K33_DisplayPoint(id, arr, 2);

		// Turn off the colon
		HT16K33_DisplayColon(id, 0);

		return DISPLAY_STATUS_OK;
}

PUBLIC DisplayStatusID_t Seg_Display_Bang(SegDisplayIndex id) {
    static uint8_t bang[4] = {SEG7_B, SEG7_A, SEG7_N, SEG7_G};
    HT16K33_Display(id, bang);
    return DISPLAY_STATUS_OK;
}

PUBLIC DisplayStatusID_t Seg_Display_Volt(SegDisplayIndex id) {
	static uint8_t volt[4] = {SEG7_P, SEG7_0, SEG7_L, SEG7_t};
	HT16K33_Display(id, volt);
	return DISPLAY_STATUS_OK;
}
