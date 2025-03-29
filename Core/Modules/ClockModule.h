/*
 * ClockModule.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef MODULES_CLOCKMODULE_H_
#define MODULES_CLOCKMODULE_H_

#include "ApplicationTypes.h"
#include "cmsis_os.h"

static uint32_t colorPicker;

void ClockModule_Init();
void ClockModule_Update();

#endif /* MODULES_CLOCKMODULE_H_ */
