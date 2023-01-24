/*
 * SpeedTask.c
 *
 *  Created on: Jan 24, 2023
 *      Author: jeremycote
 *
 *  This is the task for managing the speed sensor input
 *
 */

#include "SpeedTask.h"
#include "SpeedModule.h"
#include "SerialDebugDriver.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityHigh2
#define TIMER_SPEED_TASK 100UL

const char SPT_TAG[] = "#SPT:";

osThreadId_t SpeedTaskHandle;
const osThreadAttr_t SpeedTask_attributes = {
	.name = "SpeedTask",
	.stack_size = STACK_SIZE,
	.priority = SPEED_TASK_PRIORITY,
};

PUBLIC void InitSpeedTask(void)
{

	SpeedTaskHandle = osThreadNew(SpeedTask, NULL, &SpeedTask_attributes);

}
PRIVATE void SpeedTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("speed");

	for(;;)
	{
		cycleTick += TIMER_SPEED_TASK;
		osDelayUntil(cycleTick);
		DebugPrint("%s speed loop", SPT_TAG);
		Speed_UpdateSpeed();
	}
}
