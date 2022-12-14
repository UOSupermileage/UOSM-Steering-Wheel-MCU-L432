/*
 * ThrottleTask.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *
 *  This is the module for managing the throttle input and sending to the rest of the car
 *
 */

#include "ThrottleTask.h"
#include "ThrottleModule.h"
#include "SerialDebugDriver.h"
#include "InternalCommsModule.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*4
#define THROTTLE_TASK_PRIORITY (osPriority_t) osPriorityHigh1
#define TIMER_THROTTLE_TASK 1000UL

PUBLIC void InitThrottleTask(void);
PRIVATE void ThrottleTask(void *argument);

osThreadId_t ThrottleTaskHandle;
const osThreadAttr_t ThrottleTask_attributes = {
	.name = "ThrottleTask",
	.stack_size = STACK_SIZE,
	.priority = THROTTLE_TASK_PRIORITY,
};

PUBLIC void InitThrottleTask(void)
{

	ThrottleTaskHandle = osThreadNew(ThrottleTask, NULL, &ThrottleTask_attributes);

}
PRIVATE void ThrottleTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("throttle");

	for(;;)
	{
		cycleTick += TIMER_THROTTLE_TASK;
		osDelayUntil(cycleTick);
		DebugPrint("throttle loop");

	}
}
