/*
 * ThrottleTask.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *
 *  This is the module for managing the throttle input and sending to the rest of the car
 *  Can only import interface files
 */

#include "ThrottleTask.h"
#include "ThrottleModule.h"

#define STACK_SIZE 128
#define THROTTLE_TASK_PRIORITY (osPriority_t) osPriorityHigh1
#define TIMER_THROTTLE_TASK 1000UL

extern UART_HandleTypeDef huart2;

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
	HAL_UART_Transmit(&huart2, "throttle\n\r", 10, HAL_MAX_DELAY);

	for(;;)
	{
		cycleTick += TIMER_THROTTLE_TASK;
		osDelayUntil(cycleTick);
		HAL_UART_Transmit(&huart2, "throttle loop\n\r", 15, HAL_MAX_DELAY);

	}
}
