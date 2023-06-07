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

/// @brief Returns the number of digits present in an integer
/// @param number 
/// @return uint8_t 
PRIVATE uint8_t Seg_Display_DigitCtr(uint8_t number){
	int result = 0;
	while(number!=0){
		number=number/10; //Integer division by 10 to reduce the number by one digit
		result++;
	}
	return result;
}

PUBLIC DisplayStatusID_t Seg_Display_Float(SegDisplayIndex id, float num)
{
    if (num < 0){ //check for negative float
        return DISPLAY_ERROR_FLOAT_VALUE;
    }

    else if (num == 0){
        uint8_t zeroArr[4] = {0,0,0,0};
        HT16K33_Display(id, zeroArr);
        return DISPLAY_STATUS_OK;
    }

    else {
        // decimal point position is initial decimal size - integer size
        uint8_t flag = 1;

        uint8_t integerPart;
        uint8_t decimalPos = 0;

        double deciPart;

        while (flag)
        {
            num = num * 10; //left shift number by one decimal digit
            integerPart = (int)num; //cast and save new number
            deciPart = num - integerPart;
            decimalPos++;
            if (deciPart == 0) //stop when there is no more decimal remaining
            {
                flag = 0;
            }
        }

        int size = Seg_Display_DigitCtr(integerPart); //number of digits of the converted number
        int point = (size - decimalPos) - 1; //location of where the point should appear on the display
        uint8_t arr[size];

        for (int i = size - 1; i > -1; i--) //store each digit of the integer as a single int in an array
        {
            uint8_t item = integerPart % 10;
            integerPart = integerPart / 10;
            arr[i] = item;
        }

        // check for when there is a float beginning with zero, and then right shift the array by 1
        if ((point < 0))
        {
            int f = arr[0];  // current element
            int flagone = 1; // first item flag
            for (int i = 0; i < size; i++)
            {
                if (flagone)
                {
                    arr[0] = 0;
                    flagone = 0;
                    continue;
                }
                int temp = arr[i];
                arr[i] = f;
                f = temp;
            }
            HT16K33_DisplayPoint(id, arr, 0);
            return DISPLAY_STATUS_OK;
        }
        else
        { // regular float, with decimal placement at value of point
            HT16K33_DisplayPoint(id, arr, point);
            return DISPLAY_STATUS_OK;
        }
    }
}

PUBLIC DisplayStatusID_t Seg_Display_SystemError(SegDisplayIndex id, char letter){
    uint8_t error_codes[5] = {SEG7_A, SEG7_B, SEG7_D, SEG7_E, SEG7_F};
    char access_key[5] = {'A','B','D','E','F'};

    uint8_t fail [4] = {15, 10 ,18,19 };

    uint8_t fault[4] = {SEG7_C,SEG7_NONE, 0, SEG7_NONE} ;
    uint8_t found = 0;
    for (int i = 0; i < 5; i++){
        if (letter == access_key[i]){
        	found = 1;
            fault[2] = error_codes[i];
        }
    }
    if (found == 1){
    	HAL_Delay(500);
    	HT16K33_Display(id, fail);
    	HAL_Delay(500);
		HT16K33_DisplayColon(id, 1);
		HT16K33_Display(id, fault);
		HAL_Delay(1500);
		HT16K33_DisplayColon(id, 0);
		return DISPLAY_STATUS_OK;

    }
    else {
    	return DISPLAY_ERROR_CHAR_VALUE_NOT_FOUND;
    }
}

PUBLIC DisplayStatusID_t Seg_Display_Time(SegDisplayIndex id, seconds_t seconds) {
	if (seconds <= 0) {
        uint8_t zeroArr[4] = {0,0,0,0};
        HT16K33_Display(id, zeroArr);
        return DISPLAY_STATUS_OK;
	}

	HT16K33_DisplayTime(id, seconds / 60, seconds % 60, 1);
	return DISPLAY_STATUS_OK;
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

PUBLIC DisplayStatusID_t Seg_Display_Bang(SegDisplayIndex id) {
    static uint8_t bang[4] = {SEG7_B, SEG7_A, SEG7_N, SEG7_G};
    HT16K33_Display(id, bang);
    return DISPLAY_STATUS_OK;
}

PUBLIC DisplayStatusID_t Seg_Display_Volt(SegDisplayIndex id) {
	static uint8_t volt[4] = {SEG7_U, SEG7_0, SEG7_L, SEG7_t};
	HT16K33_Display(id, volt);
	return DISPLAY_STATUS_OK;
}
