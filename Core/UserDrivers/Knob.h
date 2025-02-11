//
// Created by Pc on 2025-01-31.
//

#ifndef UOSM_STEERINGWHEEL_L432_KNOB_H
#define UOSM_STEERINGWHEEL_L432_KNOB_H

#include "stm32l4xx_hal.h"

void KnobInit(void);  // Initialize the knob
uint16_t KnobGetValue();
void KnobClearValue();

#endif // UOSM_STEERINGWHEEL_L432_KNOB_H
