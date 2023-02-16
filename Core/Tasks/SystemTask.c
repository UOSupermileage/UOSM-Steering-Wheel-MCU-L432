/*
 * SystemTask.c
 *
 *  Created on: Jan 5, 2023
 *      Author: mingy
 *
 *  This task will manage safety devices such as lights, updating the display with info from the steering wheel mcu, process user input from the steering wheel buttons
 */

/*
 * SystemInfoTask.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *
 *  This is the Task for updating the display with info from the steering wheel mcu and the car's intercommunication network
 *  Can only import Module files
 */
#include "SystemTask.h"
#include "InternalCommsModule.h"

// System info imports
#include "DataAggregation.h"
#include "DisplayModule.h"
#include "ClockModule.h"

// Safety imports
#include "LightsModule.h"

#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*4
#define SYSTEM_PRIORITY (osPriority_t) osPriorityHigh2
#define TIMER_SYSTEM_TASK 500UL

PUBLIC void InitSystemTask(void);
PRIVATE void SystemTask(void *argument);

osThreadId_t SystemTaskHandle;
const osThreadAttr_t SystemTask_attributes = {
	.name = "SystemTask",
	.stack_size = STACK_SIZE,
	.priority = SYSTEM_PRIORITY,
};

PUBLIC void InitSystemTask(void)
{

	SystemTaskHandle = osThreadNew(SystemTask, NULL, &SystemTask_attributes);

}

PRIVATE void SystemTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("system");

	ClockModule_Init();

	for(;;)
	{
		cycleTick += TIMER_SYSTEM_TASK;
		osDelayUntil(cycleTick);
		DebugPrint("sys loop");

		DebugPrint("Timer Running [%d], Time: [%d]", SystemGetTimerRunning() == Set, SystemGetRunTime());


		// Check timer
		ClockModule_Update();
	}
}

