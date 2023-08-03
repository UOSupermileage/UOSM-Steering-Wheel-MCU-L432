/*
 * SegDisplayTask.c
 *
 *  Created on: Feb 8, 2023
 *      Author: jeremycote
 */

#include "SegDisplayTask.h"

#include "I2CDisplayDriver.h"
#include "ClockModule.h"
#include "DataAggregation.h"
#include "InteruptModule.h"

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityHigh4

#define TIMER_SEGDISPLAY_TASK 500UL

const char SDT_TAG[] = "#SDT:";

osThreadId_t SegDisplayTaskHandle;
const osThreadAttr_t SegDisplayTask_attributes = {
	.name = "SegDisplayTask",
	.stack_size = STACK_SIZE,
	.priority = SPEED_TASK_PRIORITY,
};

PUBLIC void InitSegDisplayTask(void)
{
	SegDisplayTaskHandle = osThreadNew(SegDisplayTask, NULL, &SegDisplayTask_attributes);
}

static volatile int8_t showVoltage = 0;

static void Voltage_ToggleCallback() {
	if (showVoltage == 0) {
		showVoltage = 1;
	} else {
		showVoltage = 0;
	}
}

PRIVATE void SegDisplayTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();

	DebugPrint("%s 7 segment display", SDT_TAG);

	Seg_Display_Initialize(DISPLAY_0);
	Seg_Display_Initialize(DISPLAY_1);

	InteruptRegisterCallback(INTERUPT_GPIO_0_ID, Voltage_ToggleCallback, 750);

	for(;;)
	{
		cycleTick += TIMER_SEGDISPLAY_TASK;
		osDelayUntil(cycleTick);

		DebugPrint("%s 7 seg loop. Runtime: %d", SDT_TAG, SystemGetRunTime());
		if (SystemGetUndervoltage() == Set) {
		    Seg_Display_Volt(DISPLAY_1);
		}
		else if (showVoltage == 1) {
		    		Seg_Display_Voltage(DISPLAY_1, SystemGetBatteryVoltage());
		    	}
		else if (SystemGetMotorInitializing() == Set) {
        	Seg_Display_Bang(DISPLAY_1);
    	}  else {
			// normal operation
			// Seg_Display_Time(DISPLAY_0, SystemGetRunTimeSeconds());

			HT16K33_DisplayInt(DISPLAY_1, SystemGetMotorRPM() < 0 ? SystemGetMotorRPM() * -1 : SystemGetMotorRPM());
		}

		Seg_Display_Speed(DISPLAY_0, SystemGetSpeed() / 1000, SystemGetThrottleTooHigh());

	}
}
