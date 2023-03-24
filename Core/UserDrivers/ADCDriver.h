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

#define ADC_MAX_THROTTLE (throttle_raw_t) 4040
#define ADC_MIN_THROTTLE (throttle_raw_t) 0
#define ADC_MAX_PERCENTAGE (percentage_t) 1000 // Percentage in 0.1% increments. Ex: 0 = 0%. 500 = 50%. 1000 = 100%.
#define ADC_MIN_PERCENTAGE (percentage_t) 0

PUBLIC result_t ADCGetThrottleRaw(throttle_raw_t * throttleRaw);

PUBLIC percentage_t ADCConvertThrottle(throttle_raw_t throttleRaw);

#endif /* USERDRIVERS_ADCDRIVER_H_ */
