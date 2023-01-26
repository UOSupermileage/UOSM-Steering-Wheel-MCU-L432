/*
 * DisplayModule.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef MODULES_DISPLAYMODULE_H_
#define MODULES_DISPLAYMODULE_H_

#include "ApplicationTypes.h"

// TO DO: fill these functions using I2CDisplayDriver.c
PUBLIC void DisplaySpeed(km_per_second_t speedkms);
PUBLIC void DisplayCANBusError();
PUBLIC void DisplayMotorError();
PUBLIC void DisplayTime(seconds_t timeSeconds);


#endif /* MODULES_DISPLAYMODULE_H_ */
