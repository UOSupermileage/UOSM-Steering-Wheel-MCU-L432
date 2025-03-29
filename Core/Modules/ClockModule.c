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
static uint32_t colorPicker = 0;
static void NewLapCallback() {
    SystemIncrementLap();
}

static void ToggleColorPicker() {
    if (colorPicker == 0) {
        colorPicker = 1;
        SystemSetScreenState(ScreenRed);
    } else {
        colorPicker = 0;
        SystemSetScreenState(ScreenRPM);

    }
}

static void ToggleColorScreen() {
    switch (SystemGetScreenState()) {
        case ScreenRed:
            SystemSetScreenState(ScreenGreen);
            break;
        case ScreenGreen:
            SystemSetScreenState(ScreenBlue);
            break;
        case ScreenBlue:
            SystemSetScreenState(ScreenRed);
            break;
    }
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
        case ScreenRed:
            SystemSetScreenState(ScreenRed);

        break;
        case ScreenBlue:
            SystemSetScreenState(ScreenBlue);
        break;
        case ScreenGreen:
            SystemSetScreenState(ScreenGreen);
        break;
    }
}

void ClockModule_Init() {
    InteruptRegisterCallback(INTERUPT_GPIO_3_ID, ToggleColorPicker, 500);
    InteruptRegisterCallback(INTERUPT_GPIO_11_ID, NewLapCallback, 500);
    InteruptRegisterCallback(INTERUPT_GPIO_6_ID, ToggleColorScreen, 500);
}

void ClockModule_Update() {
	if (SystemGetClockState() == CLOCK_COUNTING) {
		SystemIncrementRunTime(osKernelGetTickCount() - lastTick);
		DebugPrint("Clock time: %d", SystemGetRunTimeSeconds());
	}

	lastTick = osKernelGetTickCount();
}
