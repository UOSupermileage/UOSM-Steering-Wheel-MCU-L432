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

static uint32_t lastTick = 0;

static void NewLapCallback() {
    SystemIncrementLap();
}

static void ToggleDisplayCallback() {
    switch (SystemGetScreenState()) {

    case ScreenVoltage:
        SystemSetScreenState(ScreenRPM);
        break;
    case ScreenRPM:
        SystemSetScreenState(ScreenSpeed);
        break;
    case ScreenSpeed:
        SystemSetScreenState(ScreenVoltage);
        break;
    }
}

void ClockModule_Init() {
    InteruptRegisterCallback(INTERUPT_GPIO_3_ID, ToggleDisplayCallback, 500);
    InteruptRegisterCallback(INTERUPT_GPIO_11_ID, NewLapCallback, 500);
}

void ClockModule_Update() {
	if (SystemGetClockState() == CLOCK_COUNTING) {
		SystemIncrementRunTime(osKernelGetTickCount() - lastTick);
		DebugPrint("Clock time: %d", SystemGetRunTimeSeconds());
	}

	lastTick = osKernelGetTickCount();
}
