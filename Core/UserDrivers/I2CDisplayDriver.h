/*
 * I2CDriver.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#include <stdint.h>
#ifndef USERDRIVERS_I2CDISPLAYDRIVER_H_
#define USERDRIVERS_I2CDISPLAYDRIVER_H_

#include "ApplicationTypes.h"

#include "ht16k33.h"

typedef enum  {
	DISPLAY_STATUS_OK,
    DISPLAY_ERROR_CHAR_VALUE_NOT_FOUND,
    DISPLAY_ERROR_FLOAT_VALUE,
    DISPLAY_ERROR_UNABLE_TO_DISPLAY_FAIL,
    DISPLAY_STATUS_UNINTIALIZED,
    DISPLAY_STATUS_INITIALIZED,

} DisplayStatusID_t;

PUBLIC DisplayStatusID_t Seg_Display_Initialize(SegDisplayIndex id);

PUBLIC DisplayStatusID_t Seg_Display_Float(SegDisplayIndex id, float number);  //Prints a float number on the 7 segment display

PRIVATE uint8_t Seg_Display_DigitCtr(uint8_t number); //Returns the number of digits present in an 8 bit integer

PUBLIC DisplayStatusID_t Seg_Display_SystemError(SegDisplayIndex id, char alpha);

PUBLIC DisplayStatusID_t Seg_Display_Time(SegDisplayIndex id, seconds_t seconds); // Prints number of seconds in mm:ss format

PUBLIC DisplayStatusID_t Seg_Display_Speed(SegDisplayIndex id, speed_t speed, flag_status_t throttleTooHigh);

PUBLIC DisplayStatusID_t Seg_Display_Bang(SegDisplayIndex id);

PUBLIC DisplayStatusID_t Seg_Display_Volt(SegDisplayIndex id);

PUBLIC DisplayStatusID_t Seg_Display_Stack(SegDisplayIndex id);


PUBLIC DisplayStatusID_t Seg_Display_Voltage(SegDisplayIndex id, voltage_t n);

#endif /* USERDRIVERS_I2CDISPLAYDRIVER_H_ */
