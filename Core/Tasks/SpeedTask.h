/*
 * HallTask.h
 *
 *  Created on: Jan 24, 2023
 *      Author: jeremycote
 */

#ifndef TASKS_SPEEDTASK_H_
#define TASKS_SPEEDTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

PUBLIC void InitSpeedTask(void);
PRIVATE void SpeedTask(void *argument);

#endif /* TASKS_SPEEDTASK_H_ */
