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
#include "DataAggregation.h"
#include "InteruptModule.h"
#include "HallDriver.h"

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityHigh3
#define TIMER_SPEED_TASK 300UL

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

	HallInit();

	for(;;)
	{
		cycleTick += TIMER_SPEED_TASK;
		osDelayUntil(cycleTick);
		DebugPrint("%s Reading speed from HallDriver: %d", SPT_TAG, HallGetSpeed());
		SystemSetSpeed(HallGetSpeed());
	}
}
