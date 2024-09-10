/*
 * EncoderModule.h
 *
 *  Created on: Sep 1, 2024
 *      Author: Ogechi Ahunanya
 */

#ifndef TASKS_ENCODERDISPLAYTASK_H_
#define TASKS_ENCODERDISPLAYTASK_H_

#include "cmsis_os.h"
#include "stm32l4xx_hal.h"
#include "ApplicationTypes.h"

PUBLIC void InitEncoderDisplayTask(void);
PUBLIC void EncoderDisplayTask(void *argument);

#endif /* TASKS_ENCODERDISPLAYTASK_H_ */