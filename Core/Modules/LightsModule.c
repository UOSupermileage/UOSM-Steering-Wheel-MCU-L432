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

#define WriteLeftLight(ENABLE) 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, ENABLE);
#define WriteRightLight(ENABLE) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, ENABLE);

/**
 * Internal flag for blinking the lights.
 */
static flag_status_t lightsOn = Clear;


PUBLIC void LightsModule_Init() {
	DebugPrint("%s Init Lights Module", LTM_TAG);
}

PUBLIC void LightsModule_PeriodicJob() {

	lightsOn = !lightsOn;

	WriteLeftLight (lightsOn == Set && (ReadHazardInput() == GPIO_PIN_SET || ReadLeftInput() == GPIO_PIN_SET) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	WriteRightLight(lightsOn == Set && (ReadHazardInput() == GPIO_PIN_SET || ReadRightInput() == GPIO_PIN_SET) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	SystemSetDriverEnabled(ReadHazardInput() == GPIO_PIN_SET ? Set : Clear);

        SystemSetLightsTurningLeft(ReadLeftInput() == GPIO_PIN_SET);
        SystemSetLightsTurningRight(ReadRightInput() == GPIO_PIN_SET);
        SystemSetLightsTurningHazards(ReadHazardInput() == GPIO_PIN_SET);

}
