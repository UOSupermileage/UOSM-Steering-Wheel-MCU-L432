/*
 * SafetyTask.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef TASKS_SAFETYTASK_H_
#define TASKS_SAFETYTASK_H_


#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

#define PUBLIC
#define PRIVATE

PUBLIC void InitSafetyTask(void);
PRIVATE void SafetyTask(void *argument);

#endif /* TASKS_SAFETYTASK_H_ */
