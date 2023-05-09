/*
 * HallDriver.h
 *
 *  Created on: Jan. 23, 2023
 *      Author: jeremycote
 */

#ifndef USERDRIVERS_HALLDRIVER_H_
#define USERDRIVERS_HALLDRIVER_H_

#include "ApplicationTypes.h"
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

#define HALL_BOLTS 4
#define HALL_RADIUS 0.2667
#define HALL_CIRC HALL_RADIUS *PI_T2

PUBLIC void HallInit();
PUBLIC speed_t HallGetSpeed();

// The following two functions must be called by interupts. See HAL_TIM_IC_CaptureCallback and HAL_TIM_PeriodElapsedCallback in main.c
PUBLIC void HallCaptureCallback();

#endif /* USERDRIVERS_HALLDRIVER_H_ */
