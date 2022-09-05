/*
 * SafetyTask.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *  This is the module for managing safety devices such as lights and DM switch
 *  Can only import interface files
 */

#include "SafetyTask.h"
#include "LightsModule.h"
#include "DMModule.h"

#include <stdint.h>

#define STACK_SIZE 128
#define SAFETY_TASK_PRIORITY (osPriority_t) osPriorityHigh
#define TIMER_SAFETY_TASK 1000UL

extern UART_HandleTypeDef huart2;

PUBLIC void InitSafetyTask(void);
PRIVATE void SafetyTask(void *argument);

osThreadId_t SafetyTaskHandle;
const osThreadAttr_t SafetyTask_attributes = {
	.name = "SafetyTask",
	.stack_size = STACK_SIZE,
	.priority = SAFETY_TASK_PRIORITY,
};

PUBLIC void InitSafetyTask(void)
{

	SafetyTaskHandle = osThreadNew(SafetyTask, NULL, &SafetyTask_attributes);

}
PRIVATE void SafetyTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	HAL_UART_Transmit(&huart2, "safety\n\r", 8, HAL_MAX_DELAY);

	for(;;)
	{
		cycleTick += TIMER_SAFETY_TASK;
		osDelayUntil(cycleTick);
		HAL_UART_Transmit(&huart2, "safety loop\n\r", 13, HAL_MAX_DELAY);

	}
}
