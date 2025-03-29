//
// Created by Jeremy Cote on 2024-02-22.
// Adapted from https://github.com/pklaus/MAX6955/blob/master/MAX6955.h
//

#ifndef UOSM_STEERINGWHEEL_L432_MAX6955_H
#define UOSM_STEERINGWHEEL_L432_MAX6955_H

#include "ApplicationTypes.h"

extern I2C_HandleTypeDef hi2c1;
#define MAX6955_I2C_PORT        hi2c1
#define MAX6955_I2C_ADDRESS (0x60 << 1)

typedef enum {
    MAX6955_P0 = 0,
    MAX6955_P1 = 1
} MAX6955_DigitPlane;

typedef enum {
    MAX6955_Char_0 = 0x00,
    MAX6955_Char_1 = 0x01,
    MAX6955_Char_2 = 0x02,
    MAX6955_Char_3 = 0x03,
    MAX6955_Char_4 = 0x04,
    MAX6955_Char_5 = 0x05,
    MAX6955_Char_6 = 0x06,
    MAX6955_Char_7 = 0x07,
    MAX6955_Char_8 = 0x08,
    MAX6955_Char_9 = 0x09,
    MAX6955_Char_V = 0x76,
    MAX6955_Char_O = 0x6F,
    MAX6955_Char_L = 0x6C,
    MAX6955_Char_T = 0x78,
    MAX6955_Char_W = 0x77,
    MAX6955_Char_B = 0x62,
    MAX6955_Char_A = 0x61,
    MAX6955_Char_N = 0x6E,
    MAX6955_Char_G = 0x67,
    MAX6955_Char_K = 0x6B,
    MAX6955_Char_E = 0x65,
    MAX6955_Char_R = 0x6C,
    MAX6955_Char_Blank = 0x10,
    MAX6955_Char_Minus = 0x2D,
    MAX6955_Char_Period = 0x80
} MAX6955_Char;

result_t MAX6955_Init();
result_t MAX6955_DisplayDigits(MAX6955_DigitPlane plane, uint8_t * digits);
#endif // UOSM_STEERINGWHEEL_L432_MAX6955_H
