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
 */
void LightsModule_Init();

/**
 * Action upon state of lights in the Data Aggregate
 */
void LightsModule_PeriodicJob();

#endif /* MODULES_LIGHTSMODULE_H_ */
