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

#define ADC_MAX_THROTTLE (percentage_t) 1660
#define ADC_MIN_THROTTLE (percentage_t) 0
#define ADC_MAX_PERCENTAGE (uint16_t) 1000

PUBLIC result_t ADCGetThrottleRaw(throttle_raw_t * throttleRaw);

PUBLIC percentage_t ADCConvertThrottle(throttle_raw_t *throttleRaw);

#endif /* USERDRIVERS_ADCDRIVER_H_ */
