/*
 * SegDisplayTask.c
 *
 *  Created on: Feb 8, 2023
 *      Author: jeremycote
 */

#include "SegDisplayTask.h"
#include <stdlib.h>

#include "ClockModule.h"
#include "DataAggregation.h"
#include "I2CDisplayDriver.h"
#include "InteruptModule.h"
#include "Knob.h"

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

void InitSegDisplayTask(void)
{
	SegDisplayTaskHandle = osThreadNew(SegDisplayTask, NULL, &SegDisplayTask_attributes);
}

void SegDisplayTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();

	DebugPrint("%s 7 segment display", SDT_TAG);

        result_t isInitialized = Seg_Display_Initialize();
        KnobInit();

        // TODO: Set state using encoder wheel

	for(;;)
	{
		cycleTick += TIMER_SEGDISPLAY_TASK;
		osDelayUntil(cycleTick);

                if (!isInitialized) {
                    isInitialized = Seg_Display_Initialize();
                    continue;
                }

		DebugPrint("%s 7 seg loop. Runtime: %d", SDT_TAG, SystemGetRunTime());

                if (KnobGetValue() > 0) {
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

                    KnobClearValue();
                }


                ScreenState state = SystemGetScreenState();
                DebugPrint("Display State: %d", state);

//                if (SystemGetUndervoltage() == Set) {
//		    Seg_Display_LowVoltageError();
//		} else

                if (state == ScreenVoltage) {
                    Seg_Display_Voltage(SystemGetBatteryVoltage());
                } else if (state == ScreenSpeed) {
                    Seg_Display_Speed(SystemGetSpeed() / 1000, SystemGetThrottleTooHigh(), SystemGetMotorInitializing());
                } else if (SystemGetMotorInitializing() == Set) {
                    Seg_Display_Bang();
    	        } else {
                    Seg_Display_Int(abs(SystemGetMotorRPM()));
		}
	}
}
