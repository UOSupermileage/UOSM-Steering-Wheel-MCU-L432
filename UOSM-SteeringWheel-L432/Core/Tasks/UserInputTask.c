/*
 * UserInputTask.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingy
 *  This is the module for process user input from the steering wheel buttons. may raise flags to trigger other tasks
 *  Can only import interface files
 */

#include "UserInputTask.h"
#include "UserButtonsModule.h"


#define STACK_SIZE 128
#define USER_INPUT_TASK_PRIORITY (osPriority_t) osPriorityHigh3
#define TIMER_USER_INPUT_TASK 700UL

// move this to driver function, serialdebug file
extern UART_HandleTypeDef huart2;

PUBLIC void InitUserInputTask(void);
PRIVATE void UserInputTask(void *argument);

osThreadId_t UserInputTaskHandle;
const osThreadAttr_t UserInputTask_attributes = {
	.name = "UserInputTask",
	.stack_size = STACK_SIZE,
	.priority = USER_INPUT_TASK_PRIORITY,
};

PUBLIC void InitUserInputTask(void)
{

	UserInputTaskHandle = osThreadNew(UserInputTask, NULL, &UserInputTask_attributes);

}
PRIVATE void UserInputTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	HAL_UART_Transmit(&huart2, "user input\n\r", 11, HAL_MAX_DELAY);

	for(;;)
	{
		cycleTick += TIMER_USER_INPUT_TASK;
		osDelayUntil(cycleTick);
		HAL_UART_Transmit(&huart2, "user input loop\n\r", 17, HAL_MAX_DELAY);

	}
}
