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

result_t Seg_Display_Initialize();

result_t Seg_Display_Speed(speed_t speed, flag_status_t throttleTooHigh, flag_status_t motor_initializing);

result_t Seg_Display_Bang();

result_t Seg_Display_LowVoltageError();

result_t Seg_Display_Int(int32_t value);

result_t Seg_Display_Voltage(voltage_t voltage);

#endif /* USERDRIVERS_I2CDISPLAYDRIVER_H_ */
