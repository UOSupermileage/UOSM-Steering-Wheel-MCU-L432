/*
 * ClockModule.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen, Ogechi Ahunanya
 *  This is the module for managing a clock for the driver to time laps
 *  Can only import interface files
 */

#include "ClockModule.h"

#include "DataAggregation.h"
#include "InteruptModule.h"
#include <stdbool.h>

#define HIGH 1
#define LOW 0

static uint32_t lastTick = 0;

static void NewLapCallback() {
    SystemSetNewLap(Set);
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
static void ToggleDisplayCallbackEncoder() {

    bool tick = false;

    // Determine direction based on the phase difference between A and B
    if (HAL_GPIO_ReadPin(GPIOA, INTERUPT_GPIO_12_ID) == HIGH) {
        if (HAL_GPIO_ReadPin(GPIOB, INTERUPT_GPIO_7_ID) == LOW) {
            // Clockwise rotation (increment tick counter)
            tick = true;
        } else {
            // Counterclockwise rotation (decrement tick counter)
            tick = false;
        }
    }

    // Check if tick count reaches threshold for forward or reverse switch
    if (tick) {
        // Switch to the next screen when rotating clockwise
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
    } else {
        // Switch to the previous screen when rotating counterclockwise
        switch (SystemGetScreenState()) {
            case ScreenVoltage:
                SystemSetScreenState(ScreenSpeed);
                break;
            case ScreenRPM:
                SystemSetScreenState(ScreenVoltage);
                break;
            case ScreenSpeed:
                SystemSetScreenState(ScreenRPM);
                break;
        }
    }
}


PUBLIC void ClockModule_Init() {
    InteruptRegisterCallback(INTERUPT_GPIO_3_ID, ToggleDisplayCallback, 500);
    InteruptRegisterCallback(INTERUPT_GPIO_11_ID, NewLapCallback, 1000);
    InteruptRegisterCallback(INTERUPT_GPIO_7_ID, ToggleDisplayCallbackEncoder, 500);
    InteruptRegisterCallback(INTERUPT_GPIO_12_ID, ToggleDisplayCallbackEncoder, 500);

}

PUBLIC void ClockModule_Update() {
	if (SystemGetClockState() == CLOCK_COUNTING) {
		SystemIncrementRunTime(osKernelGetTickCount() - lastTick);
		DebugPrint("Clock time: %d", SystemGetRunTimeSeconds());
	}

	lastTick = osKernelGetTickCount();
}
