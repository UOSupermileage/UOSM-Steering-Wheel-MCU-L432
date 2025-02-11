//
// Created by Pc on 2025-01-31.
//
#include "Knob.h"
#include "InteruptModule.h"
#include <stdio.h>

static volatile uint16_t knob_position = 0;  // Store the current knob position

void KnobHandler(void) {
    knob_position++;
}

uint16_t KnobGetValue() {
    return knob_position;
}

void KnobClearValue() {
    knob_position = 0;
}

void KnobInit(void) {
    // Register knob interrupts
    InteruptRegisterCallback(INTERUPT_GPIO_12_ID, KnobHandler, 500);
    InteruptRegisterCallback(INTERUPT_GPIO_7_ID, KnobHandler, 500);
}
