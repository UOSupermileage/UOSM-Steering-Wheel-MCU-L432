/*
 * SystemInfoTask.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *
 *  This is the Task for updating the display with info from the steering wheel mcu and the car's intercommunication network
 *  Can only import Module files
 */

#include "SystemInfoTask.h"
#include "SystemInfoModule.h"
#include "ThrottleModule.h"
#include "DisplayModule.h"
#include "ClockModule.h"


#define STACK_SIZE 128
#define SYSTEM_INFO_PRIORITY (osPriority_t) osPriorityHigh2
#define TIMER_SYSTEM_INFO_TASK 1500UL

extern UART_HandleTypeDef huart2;

PUBLIC void InitSystemInfoTask(void);
PRIVATE void SystemInfoTask(void *argument);

osThreadId_t SystemInfoTaskHandle;
const osThreadAttr_t SystemInfoTask_attributes = {
	.name = "SystemInfoTask",
	.stack_size = STACK_SIZE,
	.priority = SYSTEM_INFO_PRIORITY,
};

PUBLIC void InitSystemInfoTask(void)
{

	SystemInfoTaskHandle = osThreadNew(SystemInfoTask, NULL, &SystemInfoTask_attributes);

}

PRIVATE void SystemInfoTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	HAL_UART_Transmit(&huart2, "sysinfo\n\r", 9, HAL_MAX_DELAY);

	for(;;)
	{
		cycleTick += TIMER_SYSTEM_INFO_TASK;
		osDelayUntil(cycleTick);
		HAL_UART_Transmit(&huart2, "sys loop\n\r", 12, HAL_MAX_DELAY);

	}
}
