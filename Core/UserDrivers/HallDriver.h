/*
 * HallDriver.h
 *
 *  Created on: Jan. 23, 2023
 *      Author: jeremycote
 */

#ifndef USERDRIVERS_HALLDRIVER_H_
#define USERDRIVERS_HALLDRIVER_H_

#include <stm32l4xx_hal.h>
#include "ApplicationTypes.h"

#define HALL_BOLTS  4
#define HALL_RADIUS	0.2667

PUBLIC void HallPeriodicJob();
PUBLIC speed_t HallGetSpeed();

#endif /* USERDRIVERS_HALLDRIVER_H_ */
