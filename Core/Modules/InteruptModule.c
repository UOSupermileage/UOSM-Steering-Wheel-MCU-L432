/*
 * InteruptModule.c
 *
 *  Created on: Jan 23, 2023
 *      Author: jeremycote
 */

#include "InteruptModule.h"
#include "SerialDebugDriver.h"

#include "HallDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

const char ITM_TAG[] = "#ITM:";

// Callbacks
void HallInteruptCallback();

/*********************************************************************************
 *
 * 		Look up table for Interupts and their callbacks
 *
 **********************************************************************************/

static const InteruptInfo interuptLookUpTable[NUMBER_INTERUPT_IDS] =
	{
			// Message Index			Callback
			{INTERUPT_HALL_ID,			&HallInteruptCallback}
	};

void HallInteruptCallback()
{
	HallPeriodicJob();
}

PRIVATE void InteruptTriggerCallback(InteruptLookUpIndex id) {
	interuptLookUpTable[id].interuptCallback();
}

/*********************************************************************************
 *
 * 		STM32 Interupt Callback
 *
 **********************************************************************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin) {
		case GPIO_PIN_0:
			InteruptTriggerCallback(INTERUPT_HALL_ID);
			return;
		default:
			DebugPrint("%s GPIO Pin [%d] interupt callback is not implemented", ITM_TAG, GPIO_Pin);
			return;
	}
}
