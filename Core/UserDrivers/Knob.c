//
// Created by Pc on 2025-01-31.
//
#include "Knob.h"
#include "InteruptModule.h"
#include <stdio.h>

static volatile uint16_t knob_position = 0;  // Store the current knob position

void KnobHandlerLeft(void) {
    knob_position = 2;
}
void KnobHandlerRight(void) {
    knob_position = 1;
}

uint16_t KnobGetValue() {
    int knob_pos = knob_position;
    return knob_pos;
}

void KnobClearValue() {
    knob_position = 0;
}

uint16_t KnobClicked() {

}

void KnobInit(void) {
    // Register knob interrupts
    InteruptRegisterCallback(INTERUPT_GPIO_12_ID, KnobHandlerLeft, 500);
    InteruptRegisterCallback(INTERUPT_GPIO_7_ID, KnobHandlerRight, 500);
}
