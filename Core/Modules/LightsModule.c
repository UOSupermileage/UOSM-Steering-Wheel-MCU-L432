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

#include "SerialDebugDriver.h"

static const char LTM_TAG[] = "#LTM:";

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define ReadLeftInput() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)
#define ReadRightInput() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)
#define WriteLeftLight(ENABLE) 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, ENABLE);
#define WriteRightLight(ENABLE) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, ENABLE);

/**
 * Internal flag for blinking the lights.
 */
static flag_status_t lightsOn = Clear;

static void LightsModule_HazardCallback();

PUBLIC void LightsModule_Init() {
	InteruptRegisterCallback(INTERUPT_GPIO_1_ID, LightsModule_HazardCallback, 1000);
}

PUBLIC void LightsModule_PeriodicJob() {

	lightsOn = !lightsOn;

	WriteLeftLight (lightsOn == Set && (SystemGetHazardSignal() == Set || ReadLeftInput() == GPIO_PIN_SET) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	WriteRightLight(lightsOn == Set && (SystemGetHazardSignal() == Set || ReadRightInput() == GPIO_PIN_SET) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static void LightsModule_HazardCallback() {
	DebugPrint("%s Toggling Hazards", LTM_TAG);
	SystemToggleHazardSignal();
}
