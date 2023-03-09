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

#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define ClockActionIsPressed() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET

#define LONG_PRESS 3000
#define CLOCK_DEBOUNCE 2000

static uint32_t lastTick = 0;
static uint32_t lastPressed = 0;
static uint8_t actionIsPressed = 0;
static uint8_t stateInitalised = 0;

PUBLIC void ClockModule_Init() {
	SystemSetClockState(CLOCK_WAITING);
}

const char CKM_TAG[] = "#CKM:";

static uint8_t TimeElapsed(int32_t now, int32_t before, int32_t length) {
	return now - before > length;
}

PUBLIC void ClockModule_Update() {

	switch (SystemGetClockState()) {
		case CLOCK_WAITING:

			DebugPrint("%s Button Pressed: [%d]", CKM_TAG, ClockActionIsPressed());

			if (ClockActionIsPressed()) {

				DebugPrint("%s Clock Pressed. Transitioning to COUNTING", CKM_TAG);

				SystemSetClockState(CLOCK_COUNTING);
				lastPressed = osKernelGetTickCount();
				actionIsPressed = 0;
				stateInitalised = 0;
			}

			break;
		case CLOCK_COUNTING:
			SystemIncrementRunTime(osKernelGetTickCount() - lastTick);
			lastTick = osKernelGetTickCount();

			// Check if counting has run for at least CLOCK_DEBOUNCE
			if (!stateInitalised) {
				if (TimeElapsed(lastTick, lastPressed, CLOCK_DEBOUNCE)) {
					DebugPrint("Time has elapsed");
					stateInitalised = 1;
				} else {
					// Wait for debounce
					break;
				}
			}

			if (actionIsPressed) {

				if (ClockActionIsPressed()) {

					if (lastPressed > lastTick ? lastTick > LONG_PRESS : lastTick - lastPressed > LONG_PRESS) {
						SystemSetClockState(CLOCK_PAUSED);
						actionIsPressed = 0;
					}

				} else {
					// Increment lap counter
					DebugPrint("%s Increment Lap Counter", CKM_TAG);
				}

			} else {
				actionIsPressed = 1;
				lastPressed = osKernelGetTickCount();
			}

			break;
		case CLOCK_PAUSED:
			if (actionIsPressed) {

				if (ClockActionIsPressed()) {

					if (lastPressed > lastTick ? lastTick > LONG_PRESS : lastTick - lastPressed > LONG_PRESS) {

						// Long press
						SystemSetClockState(CLOCK_WAITING);
					}

				} else {
					// Increment lap counter
					DebugPrint("%s Increment Lap Counter", CKM_TAG);
					SystemSetClockState(CLOCK_COUNTING);
				}

			} else {
				actionIsPressed = 1;
				lastPressed = osKernelGetTickCount();
			}

			break;
		}

}

//PRIVATE void ClockModule_ToggleCallback() {
//
//	DebugPrint("Clock Toggle");
//
//
//
//
//	if (SystemGetTimerRunning() == Clear) {
//		// If timer is stopped. Clear it.
//		SystemClearRunTime();
//	}
//
//	SystemSetTimerRunning(SystemGetTimerRunning() == Clear ? Set : Clear);
//
//}
