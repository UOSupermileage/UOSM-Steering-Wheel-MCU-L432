/*
 * LightsModule.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef MODULES_LIGHTSMODULE_H_
#define MODULES_LIGHTSMODULE_H_

#include "ApplicationTypes.h"
#include "stm32l4xx_hal.h"

/**
 * Initialize lights module and interupts.
 *
 * MUST BE CALLED BY THE LIGHTS TASK!
 */
PUBLIC void LightsModule_Init();

/**
 * Action upon state of lights in the Data Aggregate
 */
PUBLIC void LightsModule_PeriodicJob();

PUBLIC uint8_t LightsModule_ShouldBlink();

#endif /* MODULES_LIGHTSMODULE_H_ */
