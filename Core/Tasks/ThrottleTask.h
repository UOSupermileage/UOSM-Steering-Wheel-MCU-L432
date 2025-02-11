/*
 * ThrottleTask.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingy
 */

#ifndef TASKS_THROTTLETASK_H_
#define TASKS_THROTTLETASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

void InitThrottleTask(void);
void ThrottleTask(void *argument);

#endif /* TASKS_THROTTLETASK_H_ */
