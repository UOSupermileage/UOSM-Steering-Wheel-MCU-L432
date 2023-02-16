/*
 * DisplayTask.h
 *
 *  Created on: Feb 8, 2023
 *      Author: jeremycote
 */

#ifndef TASKS_SEGDISPLAYTASK_H_
#define TASKS_SEGDISPLAYTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

PUBLIC void InitSegDisplayTask(void);
PRIVATE void SegDisplayTask(void *argument);

#endif /* TASKS_SEGDISPLAYTASK_H_ */
