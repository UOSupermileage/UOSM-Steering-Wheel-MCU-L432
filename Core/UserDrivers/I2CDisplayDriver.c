/*
 * I2CDisplayDriver.c
 *
 *  Created on: Aug 6, 2022
 *      Author: saurav g
 */
#include "I2CDisplayDriver.h"
#include "MAX6955.h"


PUBLIC result_t Seg_Display_Initialize() {
    return MAX6955_Init();
}

/**
 * Takes speed in km / hour
 */
PUBLIC result_t Seg_Display_Speed(speed_t n, flag_status_t throttleTooHigh, flag_status_t motor_initializing) {
    speed_t displayed_speed = n <= 100 ? n : 100;

    uint8_t digits[5] = {
        motor_initializing == Set ? MAX6955_Char_B : MAX6955_Char_Blank,
        throttleTooHigh == Set ? MAX6955_Char_T : MAX6955_Char_Blank,
        displayed_speed / 10,
        displayed_speed % 10,
        MAX6955_Char_K
    };

    return MAX6955_DisplayDigits(MAX6955_P0, digits);
}

PUBLIC result_t Seg_Display_Bang() {
    uint8_t digits[5] = {
        MAX6955_Char_Blank,
        MAX6955_Char_B,
        MAX6955_Char_A,
        MAX6955_Char_N,
        MAX6955_Char_G
    };

    return MAX6955_DisplayDigits(MAX6955_P0, digits);
}

PUBLIC result_t Seg_Display_LowVoltageError() {
    uint8_t digits[5] = {
        MAX6955_Char_L,
        MAX6955_Char_O,
        MAX6955_Char_W,
        MAX6955_Char_Blank,
        MAX6955_Char_V
    };

    return MAX6955_DisplayDigits(MAX6955_P0, digits);
}

PUBLIC result_t Seg_Display_Int(int32_t value) {
    int32_t displayed_int = (value > 9999 ? 9999 : (value < -9999 ? -9999 : value));

    uint8_t digits[5] = {
        displayed_int >= 0 ? MAX6955_Char_Blank : MAX6955_Char_Minus,
        displayed_int / 1000,
        (displayed_int / 100) % 10,
        (displayed_int / 10) % 10,
        displayed_int % 10
    };

    return MAX6955_DisplayDigits(MAX6955_P0, digits);
}

PUBLIC result_t Seg_Display_Voltage(voltage_t n) {
    voltage_t displayed_voltage = n <= 999 ? n : 999;

    uint8_t digits[5] = {
        MAX6955_Char_Blank,
        displayed_voltage / 100,
        (displayed_voltage / 10) % 10,
        (displayed_voltage % 10) | MAX6955_Char_Period,
        MAX6955_Char_V
    };

    return MAX6955_DisplayDigits(MAX6955_P0, digits);
}
