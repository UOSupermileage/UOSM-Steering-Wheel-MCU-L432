/*
 * EncoderModule.c
 *
 *  Created on: Sep 1, 2024
 *      Author: Ogechi
 */

#include "EncoderModule.h"
#include <stdlib.h>

#include "I2CDisplayDriver.h"
#include "DataAggregation.h"
#include "InteruptModule.h"

#define HIGH 1
#define LOW 0

static int32_t tickCount = 0; // Counter for encoder ticks, can be negative for reverse
static const int32_t MAX_TICKS = 10; // Number of ticks needed to switch screens

#define STACK_SIZE 128*4
#define SPEED_TASK_PRIORITY (osPriority_t) osPriorityHigh4

#define TIMER_SEGDISPLAY_TASK 500UL

const char EDT_TAG[] = "#EDT:";
osThreadId_t EncoderDisplayTaskHandle;
const osThreadAttr_t EncoderDisplayTask_attributes = {
	.name = "EncoderDisplayTask",
	.stack_size = STACK_SIZE,
	.priority = SPEED_TASK_PRIORITY,
};

PUBLIC void InitEncoderDisplayTask(void)
{
	EncoderDisplayTaskHandle = osThreadNew(EncoderDisplayTask, NULL, &EncoderDisplayTask_attributes);
}

// Function to determine direction and handle screen switching
PRIVATE void EncoderDisplayTask(void *argument) {
	uint32_t cycleTick = osKernelGetTickCount();

		DebugPrint("%s 7 segment display", EDT_TAG);

	        result_t isInitialized = Encoder_Display_Initialize();

		for(;;)
		{
			cycleTick += TIMER_SEGDISPLAY_TASK;
			osDelayUntil(cycleTick);

	                if (!isInitialized) {
	                    isInitialized = Encoder_Display_Initialize();
	                    continue;
	                }


			DebugPrint("%s 7 seg loop. Runtime: %d", EDT_TAG, SystemGetRunTime());

	                ScreenState state = SystemGetScreenState();
	                DebugPrint("Display State: %d", state);

	                // Determine direction based on the phase difference between A and B
	                if (HAL_GPIO_ReadPin(GPIOA, INTERUPT_GPIO_12_ID) == HIGH) {
	                    if (HAL_GPIO_ReadPin(GPIOB, INTERUPT_GPIO_7_ID) == LOW) {
	                        // Clockwise rotation (increment tick counter)
	                        tickCount++;
	                    } else {
	                        // Counterclockwise rotation (decrement tick counter)
	                        tickCount--;
	                    }
	                }

	                // Check if tick count reaches threshold for forward or reverse switch
	                if (tickCount >= MAX_TICKS) {
	                    // Switch to the next screen when rotating clockwise
	                    switch (SystemGetScreenState()) {
	                        case ScreenVoltage:
	                            SystemSetScreenState(ScreenRPM);
	                            break;
	                        case ScreenRPM:
	                            SystemSetScreenState(ScreenSpeed);
	                            break;
	                        case ScreenSpeed:
	                            SystemSetScreenState(ScreenVoltage);
	                            break;
	                    }
	                    tickCount = 0; // Reset tick counter after switching screens
	                } else if (tickCount <= -MAX_TICKS) {
	                    // Switch to the previous screen when rotating counterclockwise
	                    switch (SystemGetScreenState()) {
	                        case ScreenVoltage:
	                            SystemSetScreenState(ScreenSpeed);
	                            break;
	                        case ScreenRPM:
	                            SystemSetScreenState(ScreenVoltage);
	                            break;
	                        case ScreenSpeed:
	                            SystemSetScreenState(ScreenRPM);
	                            break;
	                    }
	                    tickCount = 0; // Reset tick counter after switching screens
	                }
		}
}


