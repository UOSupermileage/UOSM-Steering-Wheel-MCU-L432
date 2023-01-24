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

speed_t speed;

PUBLIC result_t Speed_UpdateSpeed()
{
	result_t resultStatus;
	resultStatus = HallGetSpeed(&speed);
	if(resultStatus == RESULT_FAIL)
	{
		DebugPrint("%s ERROR HallGetSpeed", SPM_TAG);
		return RESULT_FAIL;
	}
	DebugPrint("%s Speed value %d", SPM_TAG, speed);
	SystemSetSpeed(speed);
	return RESULT_OK;
}

