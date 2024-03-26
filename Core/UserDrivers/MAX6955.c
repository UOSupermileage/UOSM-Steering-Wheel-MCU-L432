//
// Created by Jeremy Cote on 2024-02-22.
//

#include "MAX6955.h"

enum MAX6955_Address {
    MAX6955_GlobalIntensityRegister = 0x02,

    // How many digits are connected
    MAX6955_ScanLimitRegister = 0x03,

    MAX6955_ConfigurationRegister = 0x04,

    // Digits are 7seg, 14seg, or 16seg
    MAX6955_DigitTypeRegister = 0x0C,

    MAX6955_Digit0_Plane0 = 0x20,
    MAX6955_Digit0_Plane1 = 0x40
};

#define MAX6955_Timeout 1000

// Digits 7 to 0 are 14-segment digits
#define MAX6955_DigitType 0xFF

// Digits 0 to 4 are connected
#define MAX6955_ScanLimit 0x4

// TODO: Double check this, but this should be a very safe 12.5mA out of 28mA maximum
#define MAX6955_Intensity 0x08
#define MAX6955_AbsoluteMaximumIntensity 0x0A

/*
 * Format: P I R T E B X S
 * P (R): Current phase of blink timing
 * I (R/W): Global or digit-by-digit intensity
 * R (W): Clears digit data in P0 and P1
 * T (W): Reset blink timing
 * E (R/W): Enable or disable blink function
 * S (R/W): Shutdown or normal operation
 *
 * 0x01 = Normal operation, global intensity, no blinking, clear digit planes on start up
 * See datasheet for more details
 */
#define MAX6955_Configuration 0b00100001

static result_t WriteRegister(uint8_t reg, uint8_t value) {
    uint8_t buffer[2];
    buffer[0] = reg;
    buffer[1] = value;

    if (HAL_I2C_Master_Transmit(&MAX6955_I2C_PORT, MAX6955_I2C_ADDRESS, buffer, 2, MAX6955_Timeout) != HAL_OK) {
        return RESULT_FAIL;
    }

    return RESULT_OK;
}

static result_t ReadRegister(uint8_t reg, uint8_t* data, uint8_t len) {
    if (HAL_I2C_Mem_Read(&MAX6955_I2C_PORT, MAX6955_I2C_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, len, MAX6955_Timeout) != HAL_OK) {
        return RESULT_FAIL;
    }

    return RESULT_OK;
}

result_t MAX6955_Init() {
    if (!WriteRegister(MAX6955_GlobalIntensityRegister, MAX6955_Intensity)) {
        return RESULT_FAIL;
    }

    if (!WriteRegister(MAX6955_DigitTypeRegister, MAX6955_DigitType)) {
        return RESULT_FAIL;
    }

    if (!WriteRegister(MAX6955_ScanLimitRegister, MAX6955_ScanLimit)) {
        return RESULT_FAIL;
    }

    // Ensure intensity register
    uint8_t intensity_data_buffer[1] = { 0xFF };
    if (!ReadRegister(MAX6955_GlobalIntensityRegister, intensity_data_buffer, 1)){
        return RESULT_FAIL;
    }

    intensity_data_buffer[0] &= 0x0F;

    // Safeguard
    if (intensity_data_buffer[0] != MAX6955_Intensity || intensity_data_buffer[0] > MAX6955_AbsoluteMaximumIntensity) {
        return RESULT_FAIL;
    }

    // Turn on the lights (MAKE SURE THE LIGHTS ARE NOT TOO BRIGHT OR THEY WILL EXPLODE)
    if (!WriteRegister(MAX6955_ConfigurationRegister, MAX6955_Configuration)) {
        return RESULT_FAIL;
    }

    return RESULT_OK;
}

static inline uint8_t GetPlaneAddress(MAX6955_DigitPlane plane) {
    if (plane == MAX6955_P0) {
        return MAX6955_Digit0_Plane0;
    } else {
        return MAX6955_Digit0_Plane1;
    }
}

/**
 *
 * @param plane Write to P0 or P1
 * @param digits 5 byte array with 5 digits to write
 * @return
 */
result_t MAX6955_DisplayDigits(MAX6955_DigitPlane plane, uint8_t * digits) {
    // This works because MAX6955 store Digits 0 to 4 in consecutive order in memory
    for (uint8_t i = 0; i < 5; i++) {
        if (!WriteRegister(MAX6955_Digit0_Plane0 + i, digits[i])) {
            return RESULT_FAIL;
        }
    }

    return RESULT_OK;
}