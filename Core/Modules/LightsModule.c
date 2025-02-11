/*
 * LightsModule.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *  This is the module for controlling car lights
 *  Can only import interface files
 */

#include "LightsModule.h"

#include "InteruptModule.h"
#include "DataAggregation.h"
#include "main.h"

static const char LTM_TAG[] = "#LTM:";

#define ReadLeftInput() HAL_GPIO_ReadPin(Turn_Signal_Right_Input_GPIO_Port, Turn_Signal_Right_Input_Pin)
#define ReadRightInput() HAL_GPIO_ReadPin(Turn_Signal_Left_Input_GPIO_Port, Turn_Signal_Left_Input_Pin)
#define ReadHazardInput() HAL_GPIO_ReadPin(Hazards_Input_GPIO_Port, Hazards_Input_Pin)
#define ReadHighBeamsInput() HAL_GPIO_ReadPin(High_Beams_Input_GPIO_Port, High_Beams_Input_Pin)

void LightsModule_Init() {
	DebugPrint("%s Init Lights Module", LTM_TAG);
}

void LightsModule_PeriodicJob() {
        SystemSetLightsTurningLeft(ReadLeftInput() == GPIO_PIN_SET);
        SystemSetLightsTurningRight(ReadRightInput() == GPIO_PIN_SET);
        SystemSetLightsTurningHazards(ReadHazardInput() == GPIO_PIN_SET);
        SystemSetLightsTurningHeadLights(ReadHighBeamsInput() == GPIO_PIN_SET);
}
