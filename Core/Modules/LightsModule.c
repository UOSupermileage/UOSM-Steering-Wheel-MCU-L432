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

static const char LTM_TAG[] = "#LTM:";

#define ReadLeftInput() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)
#define ReadRightInput() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)
#define ReadHazardInput() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)

PUBLIC void LightsModule_Init() {
	DebugPrint("%s Init Lights Module", LTM_TAG);
}

PUBLIC void LightsModule_PeriodicJob() {
        SystemSetLightsTurningLeft(ReadLeftInput() == GPIO_PIN_SET);
        SystemSetLightsTurningRight(ReadRightInput() == GPIO_PIN_SET);
        SystemSetLightsTurningHazards(ReadHazardInput() == GPIO_PIN_SET);
}
