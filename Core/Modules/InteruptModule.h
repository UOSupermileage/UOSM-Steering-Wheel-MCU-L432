/*
 * InteruptModule.h
 *
 *  Created on: Jan 23, 2023
 *      Author: jeremycote
 */

#ifndef MODULES_INTERUPTMODULE_H_
#define MODULES_INTERUPTMODULE_H_

#include "ApplicationTypes.h"

// Interupt IDs for each piece of data
#define NUMBER_INTERUPT_IDS 1

typedef enum InteruptLookUpIndex
{
	INTERUPT_HALL_ID,
} InteruptLookUpIndex;

typedef struct
{
	InteruptLookUpIndex index;
	void (*interuptCallback)();

} InteruptInfo;

PUBLIC void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

PRIVATE void InteruptTriggerCallback(InteruptLookUpIndex id);

#endif /* MODULES_INTERUPTMODULE_H_ */
