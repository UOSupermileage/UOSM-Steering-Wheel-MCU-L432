/*
 * ADCDriver.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef USERDRIVERS_ADCDRIVER_H_
#define USERDRIVERS_ADCDRIVER_H_

#include <stm32l4xx_hal.h>
#include "ApplicationTypes.h"

PUBLIC result_t ADCGetThrottleRaw(throttle_raw_t * throttleRaw);

#endif /* USERDRIVERS_ADCDRIVER_H_ */
