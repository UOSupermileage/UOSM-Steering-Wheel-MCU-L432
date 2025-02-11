/*
 * ClockTask.c
 *
 *  Created on: Feb 16, 2023
 *      Author: jeremycote
 */

#include "ClockTask.h"

#include "ClockModule.h"

#define STACK_SIZE 128*8
#define CLOCK_TASK_PRIORITY (osPriority_t) osPriorityHigh7
#define TIMER_CLOCK_TASK 500UL


const char CKT_TAG[] = "#CKT:";

void InitClockTask(void);
void ClockTask(void *argument);

osThreadId_t ClockTaskHandle;
const osThreadAttr_t ClockTask_attributes = {
	.name = "Clock",
	.stack_size = STACK_SIZE,
	.priority = CLOCK_TASK_PRIORITY,
};

void InitClockTask(void)
{

	ClockTaskHandle = osThreadNew(ClockTask, NULL, &ClockTask_attributes);

}
void ClockTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("clock");

	ClockModule_Init();

	for(;;)
	{
		cycleTick += TIMER_CLOCK_TASK;
		osDelayUntil(cycleTick);

		// Check timer
		DebugPrint("%s Clock tick", CKT_TAG);
		ClockModule_Update();
	}
}
