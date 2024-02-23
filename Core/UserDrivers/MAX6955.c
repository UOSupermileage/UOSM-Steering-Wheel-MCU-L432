//
// Created by Jeremy Cote on 2024-02-22.
//

#include "MAX6955.h"

static void MAX6955_Transmit(uint8_t byte) {
    uint8_t buffer[1] = { byte };
    HAL_I2C_Master_Transmit(&MAX6955_I2C_PORT, MAX6955_I2C_ADDRESS, buffer, 1, 1000);
}

static void MAX6955_TransmitCommand(uint8_t command, uint8_t value) {
    MAX6955_Transmit(command);
    MAX6955_Transmit(value);
}

void MAX6955_Init() {
    MAX6955_TransmitCommand(MAX6955_REGISTER_GLOBAL_INTENSITY, MAX6955_DEFAULT_INTENSITY);

    // Turn on the lights (MAKE SURE THE LIGHTS ARE NOT TOO BRIGHT OR THEY WILL EXPLODE)
    MAX6955_TransmitCommand(MAX6955_REGISTER_CONFIGURATION, 0x01);
}