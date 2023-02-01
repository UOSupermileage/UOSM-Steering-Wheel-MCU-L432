/*
 * LightsTask.h
 *
 *  Created on: Feb 1, 2023
 *      Author: jeremycote
 */

#ifndef TASKS_LIGHTSTASK_H_
#define TASKS_LIGHTSTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

PUBLIC void InitLightsTask(void);
PRIVATE void LightsTask(void *argument);


#endif /* TASKS_LIGHTSTASK_H_ */
