/*
 * LightsTask.c
 *
 *  Created on: Feb 1, 2023
 *      Author: jeremycote
 */


#include "LightsTask.h"
#include "SerialDebugDriver.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityHigh3

const char SPT_TAG[] = "#LIT:";

osThreadId_t LightsTaskHandle;
const osThreadAttr_t LightsTask_attributes = {
	.name = "LightsTask",
	.stack_size = STACK_SIZE,
	.priority = SPEED_TASK_PRIORITY,
};

PUBLIC void InitLightsTask(void)
{

	LightsTaskHandle = osThreadNew(LightsTask, NULL, &LightsTask_attributes);

}
PRIVATE void LightsTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("speed");

	// Pass 0 as debounce to disable debouncing
	InteruptRegisterCallback(INTERUPT_GPIO_8_ID, HallPeriodicJob, 0);

	for(;;)
	{
		cycleTick += TIMER_SPEED_TASK;
		osDelayUntil(cycleTick);
		DebugPrint("%s speed loop", SPT_TAG);
		Speed_UpdateSpeed();
		DebugPrint("%s Speed: %d", SPT_TAG, SystemGetSpeed());
	}
}
