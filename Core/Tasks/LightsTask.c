/*
 * LightsTask.c
 *
 *  Created on: Feb 1, 2023
 *      Author: jeremycote
 */


#include "LightsTask.h"

#include "LightsModule.h"

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityNormal

#define TIMER_LIGHTS_TASK 500UL

const char LIT_TAG[] = "#LIT:";

osThreadId_t LightsTaskHandle;
const osThreadAttr_t LightsTask_attributes = {
	.name = "LightsTask",
	.stack_size = STACK_SIZE,
	.priority = SPEED_TASK_PRIORITY,
};

void InitLightsTask(void)
{

	LightsTaskHandle = osThreadNew(LightsTask, NULL, &LightsTask_attributes);

}
void LightsTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();

	DebugPrint("%s lights", LIT_TAG);

	LightsModule_Init();

	for(;;)
	{
		cycleTick += TIMER_LIGHTS_TASK;
		osDelayUntil(cycleTick);
		LightsModule_PeriodicJob();
	}
}
