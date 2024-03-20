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

enum ScreenState {
    ScreenVoltage,
    ScreenRPM,
    ScreenSpeed
};

static volatile enum ScreenState state = ScreenSpeed;

PRIVATE void SegDisplayTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();

	DebugPrint("%s 7 segment display", SDT_TAG);

	Seg_Display_Initialize();

        // TODO: Set state using encoder wheel

	for(;;)
	{
		cycleTick += TIMER_SEGDISPLAY_TASK;
		osDelayUntil(cycleTick);

		DebugPrint("%s 7 seg loop. Runtime: %d", SDT_TAG, SystemGetRunTime());

                if (SystemGetUndervoltage() == Set) {
		    Seg_Display_LowVoltageError();
		} else if (state == ScreenVoltage) {
                    Seg_Display_Voltage(SystemGetBatteryVoltage());
                } else if (state == ScreenSpeed) {
                    Seg_Display_Speed(SystemGetSpeed() / 1000, SystemGetThrottleTooHigh(), SystemGetMotorInitializing());
                } else if (SystemGetMotorInitializing() == Set) {
                    Seg_Display_Bang();
    	        } else {
                    Seg_Display_Int(SystemGetMotorRPM());
		}
	}
}
