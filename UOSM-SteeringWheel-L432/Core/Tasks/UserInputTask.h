/*
 * UserInputTask.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef TASKS_USERINPUTTASK_H_
#define TASKS_USERINPUTTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

PUBLIC void InitUserInputTask(void);
PRIVATE void UserInputTask(void *argument);

#endif /* TASKS_USERINPUTTASK_H_ */
