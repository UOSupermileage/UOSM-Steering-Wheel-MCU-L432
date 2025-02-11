//
// Created by Pc on 2025-01-31.
//
#include "knob.h"
#include <stdio.h>
#include "InteruptModule.h"

static int knob_position = 0;  // Store the current knob position

void KnobHandler(void) {
    knob_position++;  // Adjust based on knob direction (modify if needed)

   // update_display(knob_position);  // Update the display

    printf("Knob turned! Position: %d\n", knob_position);  // Debugging
}

void knob_init(void) {
    // If the knob requires additional initialization, we add it here
    InteruptRegisterCallback(INTERUPT_GPIO_12_ID, KnobHandler, 500);

}
