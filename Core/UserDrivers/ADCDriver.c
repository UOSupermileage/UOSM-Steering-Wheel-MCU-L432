/*
 * ADCDriver.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingy
 */
#include "ADCDriver.h"

extern ADC_HandleTypeDef hadc1;

result_t ADCGetThrottleRaw(throttle_raw_t * throttleRaw)
{
	HAL_StatusTypeDef returnStatus;
	returnStatus = HAL_ADC_Start(&hadc1);
	if(returnStatus != HAL_OK)
	{
		return RESULT_FAIL;
	}

	returnStatus = HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	if(returnStatus != HAL_OK)
	{
		return RESULT_FAIL;
	}
	*throttleRaw = ADC_MAX_THROTTLE - HAL_ADC_GetValue(&hadc1);

	return RESULT_OK;
}

percentage_t ADCConvertThrottle(throttle_raw_t throttleRaw) {

	if (throttleRaw > ADC_MAX_THROTTLE) {
		return ADC_MAX_PERCENTAGE;
	}

	if (throttleRaw <= ADC_MIN_THROTTLE) {
		return ADC_MIN_PERCENTAGE;
	}

        percentage_t throttle = (throttleRaw - ADC_MIN_THROTTLE) * ADC_MAX_PERCENTAGE / ADC_MAX_THROTTLE;

        if (throttle < 20) {
            throttle = 0;
        }

	return throttle;
}
