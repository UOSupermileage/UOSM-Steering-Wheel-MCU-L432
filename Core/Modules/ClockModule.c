/*
 * ClockModule.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *  This is the module for managing a clock for the driver to time laps
 *  Can only import interface files
 */

#include "ClockModule.h"

#include "DataAggregation.h"
#include "InteruptModule.h"

#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

static uint32_t lastTick = 0;

PUBLIC void ClockModule_Init() {
	InteruptRegisterCallback(INTERUPT_GPIO_0_ID, ClockModule_ToggleCallback, 1000);
}

PUBLIC void ClockModule_Update() {
	if (SystemGetTimerRunning() == Set) {
		SystemIncrementRunTime(osKernelGetTickCount() - lastTick);
	}

	lastTick = osKernelGetTickCount();
}

PRIVATE void ClockModule_ToggleCallback() {

	DebugPrint("Clock Toggle");

	if (SystemGetTimerRunning() == Clear) {
		// If timer is stopped. Clear it.
		SystemClearRunTime();
	}

	SystemSetTimerRunning(SystemGetTimerRunning() == Clear ? Set : Clear);

}
