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
	InteruptRegisterCallback(INTERUPT_GPIO_4_ID, LightsModule_LeftTurnCallback, 10);
	InteruptRegisterCallback(INTERUPT_GPIO_5_ID, LightsModule_RightTurnCallback, 10);
}

PUBLIC void LightsModule_PeriodicJob() {

	lightsOn = !lightsOn;

	DebugPrint("%s SystemGetHazards: [%d], SystemGetLeft: [%d], SystemGetRight: [%d]", LTM_TAG, SystemGetHazardSignal() == Set, SystemGetLeftSignal() == Set, SystemGetRightSignal() == Set);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, lightsOn == Set && (SystemGetHazardSignal() == Set || SystemGetLeftSignal() == Set) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, lightsOn == Set && (SystemGetHazardSignal() == Set || SystemGetRightSignal() == Set) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

PUBLIC uint8_t LightsModule_ShouldBlink() {
	return SystemGetLeftSignal() == Set || SystemGetRightSignal() == Set || SystemGetHazardSignal() == Set;
}


/**
 * Parent callback function for lights. Specific light callbacks will wrap this callback to reduce copies of code.
 */
static void LightsModule_Callback() {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(lightsTask, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void LightsModule_LeftTurnCallback() {

//	GPIO_PinState state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
//	SystemSetLeftSignal(state == GPIO_PIN_SET ? Set : Clear);
	SystemToggleLeftSignal();
	LightsModule_Callback();
}

static void LightsModule_RightTurnCallback() {
//	GPIO_PinState state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
//
//	SystemSetRightSignal(state == GPIO_PIN_SET ? Set : Clear);
	SystemToggleRightSignal();
	LightsModule_Callback();
}

static void LightsModule_HazardCallback() {
	SystemToggleHazardSignal();
	LightsModule_Callback();
}
