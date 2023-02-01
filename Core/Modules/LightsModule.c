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

/**
 * Reference to the LightsTask to notify it when lights should change.
 */
static TaskHandle_t lightsTask;

/**
 * Internal flag for blinking the lights.
 */
static flag_status_t lightsOn = Clear;

static void LightsModule_HazardCallback();
static void LightsModule_LeftTurnCallback();
static void LightsModule_RightTurnCallback();

PUBLIC void LightsModule_Init() {
	lightsTask = xTaskGetCurrentTaskHandle();

	InteruptRegisterCallback(INTERUPT_GPIO_1_ID, LightsModule_HazardCallback, 1000);
	InteruptRegisterCallback(INTERUPT_GPIO_4_ID, LightsModule_LeftTurnCallback, 1000);
	InteruptRegisterCallback(INTERUPT_GPIO_5_ID, LightsModule_RightTurnCallback, 1000);
}

PUBLIC void LightsModule_PeriodicJob() {

	lightsOn = !lightsOn;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, lightsOn == Set && (SystemGetHazardSignal() == Set || SystemGetLeftSignal() == Set) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, lightsOn == Set && (SystemGetHazardSignal() == Set || SystemGetRightSignal() == Set) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/**
 * Parent callback function for lights. Specific light callbacks will wrap this callback to reduce copies of code.
 */
static void LightsModule_Callback(void (*callback)()) {
	callback();

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(lightsTask, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void LightsModule_LeftTurnCallback() {
	LightsModule_Callback(SystemToggleLeftSignal);
}

static void LightsModule_RightTurnCallback() {
	LightsModule_Callback(SystemToggleRightSignal);
}

static void LightsModule_HazardCallback() {
	LightsModule_Callback(SystemToggleHazardSignal);
}
