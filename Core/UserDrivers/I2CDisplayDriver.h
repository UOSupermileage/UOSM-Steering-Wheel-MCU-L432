/*
 * I2CDriver.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */


#ifndef USERDRIVERS_I2CDISPLAYDRIVER_H_
#define USERDRIVERS_I2CDISPLAYDRIVER_H_

#include "ApplicationTypes.h"

typedef enum  {
	DISPLAY_STATUS_OK,
    DISPLAY_ERROR_CHAR_VALUE_NOT_FOUND,
    DISPLAY_ERROR_FLOAT_VALUE,
    DISPLAY_ERROR_UNABLE_TO_DISPLAY_FAIL,
    DISPLAY_STATUS_UNINTIALIZED,
    DISPLAY_STATUS_INITIALIZED,

}DisplayErrorCode_t;

PUBLIC void Seg_Display_DisplayFloat(float number);  //Prints a float number on the 7 segment display

PRIVATE uint8_t digitCtr(uint8_t number); //Returns the number of digits present in an 8 bit integer

PUBLIC void Seg_Display_SystemError(char alpha); 


#endif /* USERDRIVERS_I2CDISPLAYDRIVER_H_ */
