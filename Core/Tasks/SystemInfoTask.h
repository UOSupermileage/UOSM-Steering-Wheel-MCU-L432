/*
 * SystemInfoTask.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef TASKS_SYSTEMINFOTASK_H_
#define TASKS_SYSTEMINFOTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

PUBLIC void InitSystemInfoTask(void);
PRIVATE void SystemInfoTask(void *argument);

#endif /* TASKS_SYSTEMINFOTASK_H_ */
