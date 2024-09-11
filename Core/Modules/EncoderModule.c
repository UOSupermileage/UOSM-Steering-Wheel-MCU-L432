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
#include "main.h"

#define ReadEncoderAInput() HAL_GPIO_ReadPin(EncoderA_GPIO_PORT, Encoder_A_Pin)
#define ReadEncoderBInput() HAL_GPIO_ReadPin(EncoderB_GPIO_PORT, Encoder_B_Pin)


const char EDM_TAG[] = "#EDM:";

PUBLIC void EncoderModule_Init()
{
	DebugPrint("%s Init Encoder Module", EDM_TAG);
}

// Function to determine direction and handle screen switching
PRIVATE void EncoderModule_PeriodicJob(int argument) {


	// Check if tick count reaches threshold for forward or reverse switch

	                if (argument == 1) {
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
	                } else if (argument == 0 ) {
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
	                }
		}



