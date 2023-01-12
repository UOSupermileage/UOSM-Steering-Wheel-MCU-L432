/*
 * SystemTask.h
 *
 *  Created on: Jan 9, 2023
 *      Author: mingy
 */

#ifndef TASKS_SYSTEMTASK_H_
#define TASKS_SYSTEMTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

PUBLIC void InitSystemTask(void);
PRIVATE void SystemTask(void *argument);

#endif /* TASKS_SYSTEMTASK_H_ */
