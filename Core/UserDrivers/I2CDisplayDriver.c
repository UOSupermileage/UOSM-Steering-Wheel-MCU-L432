/*
 * I2CDisplayDriver.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */
#include "I2CDisplayDriver.h"
#include "ht16k33.h"


PUBLIC DisplayStatusID_t Seg_Display_Initialize(void) {
	seg7_init();
    return DISPLAY_STATUS_INITIALIZED;

}

/// @brief Returns the number of digits present in an integer
/// @param number 
/// @return uint8_t 
PRIVATE uint8_t digitCtr(uint8_t number){
	int result = 0;
	while(number!=0){
		number=number/10; //Integer division by 10 to reduce the number by one digit
		result++;
	}
	return result;
 }
PUBLIC DisplayStatusID_t Seg_Display_Float(float num)
{
    if (num < 0){ //check for negative float
        return DISPLAY_ERROR_FLOAT_VALUE;
    }

    else if (num == 0){
        uint8_t zeroArr[4] = {0,0,0,0};
        seg7_display(zeroArr);
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

        int size = digitCtr(integerPart); //number of digits of the converted number
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
            seg7_displayPoint(arr, 0);
            return DISPLAY_STATUS_OK;
        }
        else
        { // regular float, with decimal placement at value of point
            seg7_displayPoint(arr, point);
            return DISPLAY_STATUS_OK;
        }
    }
}


PUBLIC DisplayStatusID_t Seg_Display_SystemError(char letter){
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
    	seg7_display(fail);
    	HAL_Delay(500);
		seg7_displayColon(1);
		seg7_display(fault);
		HAL_Delay(1500);
		seg7_displayColon(0);
		return DISPLAY_STATUS_OK;

    }
    else {
    	return DISPLAY_ERROR_CHAR_VALUE_NOT_FOUND;
    }

}
