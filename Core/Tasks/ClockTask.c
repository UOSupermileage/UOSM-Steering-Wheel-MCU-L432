/*
 * ClockTask.c
 *
 *  Created on: Feb 16, 2023
 *      Author: jeremycote
 */

#include "ClockTask.h"

#include "ClockModule.h"

#include "SerialDebugDriver.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*8
#define CLOCK_TASK_PRIORITY (osPriority_t) osPriorityNormal
#define TIMER_CLOCK_TASK 500UL


const char CKT_TAG[] = "#CKT:";

PUBLIC void InitClockTask(void);
PRIVATE void ClockTask(void *argument);

osThreadId_t ClockTaskHandle;
const osThreadAttr_t ClockTask_attributes = {
	.name = "Clock",
	.stack_size = STACK_SIZE,
	.priority = CLOCK_TASK_PRIORITY,
};

PUBLIC void InitClockTask(void)
{

	ClockTaskHandle = osThreadNew(ClockTask, NULL, &ClockTask_attributes);

}
PRIVATE void ClockTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("clock");

//	ClockModule_Init();

	for(;;)
	{
		cycleTick += TIMER_CLOCK_TASK;
		osDelayUntil(cycleTick);

		// Check timer
		DebugPrint("Clock");
//		ClockModule_Update();
	}
}
