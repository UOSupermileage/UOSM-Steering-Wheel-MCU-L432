/*
 * EncoderTask.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Ogechi
 */

#ifndef TASKS_ENCODERTASK_H_
#define TASKS_ENCODERTASK_H_

#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

#include "ApplicationTypes.h"

PUBLIC void InitEncoderTask(void);
PRIVATE void EncoderTask(void *argument);

#endif /* TASKS_ENCODERTASK_H_ */
