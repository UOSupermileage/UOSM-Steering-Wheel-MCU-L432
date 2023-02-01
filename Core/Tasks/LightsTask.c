/*
 * LightsTask.c
 *
 *  Created on: Feb 1, 2023
 *      Author: jeremycote
 */


#include "LightsTask.h"

#include "LightsModule.h"
#include "DataAggregation.h"

#include "SerialDebugDriver.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityHigh3

#define LIGHTS_BLINK_INTERVAL 250UL

const char LIT_TAG[] = "#LIT:";

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
	DebugPrint("lights");

	static uint32_t lights_notification;

	LightsModule_Init();

	for(;;)
	{
		/**
		 * Sleep until we are notified of a state change by an interrupt handler.
		 *
		 * pdTrue will clear the notification value back to 0. This effectivly makes the notification value act like a binary (rather than a counting) semaphore.
		 */

		lights_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		if (lights_notification){
			uint32_t cycleTick = osKernelGetTickCount();

			// Action upon lights until all signals are disabled
			while (SystemGetLeftSignal() == Set || SystemGetRightSignal() == Set || SystemGetHazardSignal() == Set) {

				cycleTick += LIGHTS_BLINK_INTERVAL;
				osDelayUntil(cycleTick);

				LightsModule_PeriodicJob();
			}

			// Clear any notifications that may have arrived while in the while loop.
			// TODO: May need to be replaced wiht xTaskGetCurrentTaskHandle(); Confirm on an STM32.
			xTaskNotifyStateClear(LightsTaskHandle);
		}
	}
}
