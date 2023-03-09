/*
 * HallDriver.h
 *
 *  Created on: Jan. 23, 2023
 *      Author: jeremycote
 */

#ifndef USERDRIVERS_HALLDRIVER_H_
#define USERDRIVERS_HALLDRIVER_H_

#include <stm32l4xx_hal.h>
#include "cmsis_os.h"
#include "ApplicationTypes.h"

#define HALL_BOLTS  4
#define HALL_RADIUS	0.2667
#define HALL_CIRC HALL_RADIUS * PI_T2

PUBLIC void HallInit();
PUBLIC speed_t HallGetSpeed();
PUBLIC void HallIRQHandler();

//PUBLIC void HallPeriodicJob();
//PUBLIC result_t HallConvertSpeed();

#endif /* USERDRIVERS_HALLDRIVER_H_ */
