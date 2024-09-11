/*
 * EncoderModule.c
 *
 *  Created on: Sep 10, 2024
 *      Author: Ogechi
 */
#include "EncoderTask.h"
#include "InteruptModule.h"
 
#include "EncoderModule.h"
#include "main.h"
 
#define ReadEncoderAInput() HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)
#define ReadEncoderBInput() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)
#define HIGH 1
#define LOW 0

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityHigh4

#define TIMER_ENCODER_TASK 500UL
static int32_t tickCount = 0;
static const int32_t MAX_TICKS = 10;

const char EIT_TAG[] = "#EIT:";

osThreadId_t EncoderTaskHandle;
const osThreadAttr_t EncoderTask_attributes = {
	.name = "EncoderTask",
	.stack_size = STACK_SIZE,
	.priority = SPEED_TASK_PRIORITY,
};

PUBLIC void InitEncoderTask(void)
{

	EncoderTaskHandle = osThreadNew(EncoderTask, NULL, &EncoderTask_attributes);

}

PRIVATE void EncoderTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();

	DebugPrint("%s encoder", EIT_TAG);

	EncoderModule_Init();

	for(;;)
	{
		cycleTick += TIMER_ENCODER_TASK;
		osDelayUntil(cycleTick);
		if (ReadEncoderAInput()== HIGH) {
	                    if (ReadEncoderBInput() == LOW) {
	                        // Clockwise rotation (increment tick counter)
	                        tickCount++;
	                    } else {
	                        // Counterclockwise rotation (decrement tick counter)
	                        tickCount--;
	                    }
	                }
		if (tickCount >= MAX_TICKS) {
	                    // Switch to the next screen when rotating clockwise
	                    EncoderModule_PeriodicJob( 1);
	              
	                    tickCount = 0; // Reset tick counter after switching screens
	                } else if (tickCount <= -MAX_TICKS) {
	                    // Switch to the previous screen when rotating counterclockwise
	                    EncoderModule_PeriodicJob(0);
	                  
	                    tickCount = 0; // Reset tick counter after switching screens
	                }
	                
	}
}
 
