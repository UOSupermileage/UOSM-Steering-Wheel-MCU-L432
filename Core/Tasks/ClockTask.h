/*
 * ClockTask.h
 *
 *  Created on: Feb 16, 2023
 *      Author: jeremycote
 */

#ifndef TASKS_CLOCKTASK_H_
#define TASKS_CLOCKTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"


PUBLIC void InitClockTask(void);
PRIVATE void ClockTask(void *argument);


#endif /* TASKS_CLOCKTASK_H_ */
