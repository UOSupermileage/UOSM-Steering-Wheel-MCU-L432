//
// Created by Pc on 2025-01-31.
//

#ifndef UOSM_STEERINGWHEEL_L432_KNOB_H
#define UOSM_STEERINGWHEEL_L432_KNOB_H


#include "stm32l4xx_hal.h"

void knob_init(void);  // Initialize the knob (if needed)
void knob_handler(void);  // Handle the knob turn event

#endif // UOSM_STEERINGWHEEL_L432_KNOB_H
