/*
 * LightsModule.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef MODULES_LIGHTSMODULE_H_
#define MODULES_LIGHTSMODULE_H_

#include "ApplicationTypes.h"

// TO DO: fill these functions
PUBLIC void TurnLightsOff();
PUBLIC void LeftTurnLightOn();
PUBLIC void RightTurnLightOn();
PUBLIC void HazardLightOn();

PUBLIC void LeftTurnCallback(); // When the interrupt is called for left turn, the callback triggers
PUBLIC void RightTurnCallback();
PUBLIC void HazardLightsCallback();

#endif /* MODULES_LIGHTSMODULE_H_ */
