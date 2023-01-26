/*
 * ClockModule.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef MODULES_CLOCKMODULE_H_
#define MODULES_CLOCKMODULE_H_
#include "ApplicationTypes.h"

// TO DO:
PUBLIC void ClockModule_Init(uint16_t tickDuration); // tickDuration - how long each tick is in ms
PUBLIC void ClockModule_Update();
PUBLIC void ClockModule_ButtonCallback();

#endif /* MODULES_CLOCKMODULE_H_ */
