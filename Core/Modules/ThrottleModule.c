/*
 * ThrottleModule.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingy
 *  This is the module for getting the throttle value from the steering wheel and sending it over the car's intercommunication network
 *  Can only import interface files
 */

#include "ThrottleModule.h"
#include "ADCDriver.h"

const char DBG_TAG[] = "#THM:";

throttle_raw_t adcThrottleRaw;

PUBLIC result_t Throttle_UpdateThrottle()
{
	result_t resultStatus;
	resultStatus = ADCGetThrottleRaw(&adcThrottleRaw);
	if(resultStatus == RESULT_FAIL)
	{
		DebugPrint("%s ERROR ADCGetThrottleRaw", DBG_TAG);
		return RESULT_FAIL;
	}
	DebugPrint("%s ADC value %d", DBG_TAG, adcThrottleRaw);
	SystemSetThrottleRaw(adcThrottleRaw);
	return RESULT_OK;
}

