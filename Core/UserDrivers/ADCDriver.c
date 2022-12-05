/*
 * ADCDriver.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingy
 */
#include "ADCDriver.h"

extern ADC_HandleTypeDef hadc1;

PUBLIC result_t ADCGetThrottleRaw(throttle_raw_t * throttleRaw)
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
	*throttleRaw = HAL_ADC_GetValue(&hadc1);

	return RESULT_OK;
}
