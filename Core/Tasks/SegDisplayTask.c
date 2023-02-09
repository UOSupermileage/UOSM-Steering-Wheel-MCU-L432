/*
 * SegDisplayTask.c
 *
 *  Created on: Feb 8, 2023
 *      Author: jeremycote
 */

#include "SegDisplayTask.h"

#include "I2CDisplayDriver.h"

#include "SerialDebugDriver.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityHigh4

#define TIMER_SEGDISPLAY_TASK 250UL

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

	DisplayStatusID_t statusDisplay0 = DISPLAY_STATUS_UNINTIALIZED;
	DisplayStatusID_t statusDisplay1 = DISPLAY_STATUS_UNINTIALIZED;

	for(;;)
	{
		cycleTick += TIMER_SEGDISPLAY_TASK;
		osDelayUntil(cycleTick);

		DebugPrint("%s 7 seg loop", SDT_TAG);

		if (statusDisplay0 == DISPLAY_STATUS_INITIALIZED) {
			// Display is initialized. Display necessary data.
			Seg_Display_Float(DISPLAY_0, 1.234);
		} else {
			DebugPrint("%s Initializing Display 0", SDT_TAG);
			statusDisplay0 = Seg_Display_Initialize(DISPLAY_0);
		}

		if (statusDisplay1 == DISPLAY_STATUS_INITIALIZED) {
			// Display is initialized. Display necessary data.
			Seg_Display_Float(DISPLAY_1, 5.678);
		} else {
			DebugPrint("%s Initializing Display 1", SDT_TAG);
			statusDisplay1 = Seg_Display_Initialize(DISPLAY_1);
		}
	}
}
