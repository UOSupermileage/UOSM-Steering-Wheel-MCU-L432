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
PRIVATE void SegDisplayTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();

	DebugPrint("%s 7 segment display", SDT_TAG);

	Seg_Display_Initialize(DISPLAY_0);
	Seg_Display_Initialize(DISPLAY_1);

	for(;;)
	{
		cycleTick += TIMER_SEGDISPLAY_TASK;
		osDelayUntil(cycleTick);

//		DebugPrint("%s 7 seg loop. Runtime: %d", SDT_TAG, SystemGetRunTime());

		if (SystemGetMotorInitializing() == Set) {
        	Seg_Display_Bang(DISPLAY_0);
    	} else if (SystemGetUndervoltage() == Set) {
    		Seg_Display_Volt(DISPLAY_0);
    	} else {
			// normal operation
			// Seg_Display_Time(DISPLAY_0, SystemGetRunTimeSeconds());

			HT16K33_DisplayInt(DISPLAY_0, SystemGetMotorRPM() < 0 ? SystemGetMotorRPM() * -1 : SystemGetMotorRPM());
		}

		Seg_Display_Speed(DISPLAY_1, SystemGetSpeed() / 1000, SystemGetThrottleTooHigh());

	}
}
