/*
 * SpeedModule.c
 *
 *  Created on: Jan 24, 2023
 *      Author: jeremycote
 *  This is the module for getting the current speed from the hall sensor and sending it over the car's intercommunication network
 *  Can only import interface files
 */

#include "ThrottleModule.h"
#include "HallDriver.h"
#include "SerialDebugDriver.h"

static const char SPM_TAG[] = "#SPM:";

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

PUBLIC result_t Speed_UpdateSpeed()
{
	result_t resultStatus;
	resultStatus = HallConvertSpeed();
	if(resultStatus == RESULT_FAIL)
	{
		DebugPrint("%s ERROR HallGetSpeed", SPM_TAG);
		return RESULT_FAIL;
	}
	return RESULT_OK;
}

