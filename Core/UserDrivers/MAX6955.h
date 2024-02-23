//
// Created by Jeremy Cote on 2024-02-22.
// Adapted from https://github.com/pklaus/MAX6955/blob/master/MAX6955.h
//

#ifndef UOSM_STEERINGWHEEL_L432_MAX6955_H
#define UOSM_STEERINGWHEEL_L432_MAX6955_H

#include "ApplicationTypes.h"

#define MAX6955_REGISTER_GLOBAL_INTENSITY 0x02
#define MAX6955_REGISTER_CONFIGURATION 0x04

#define MAX6955_DEFAULT_INTENSITY 0x04

extern I2C_HandleTypeDef hi2c1;
#define MAX6955_I2C_PORT        hi2c1
#define MAX6955_I2C_ADDRESS 0x70 // TODO: Choose the correct address

#endif // UOSM_STEERINGWHEEL_L432_MAX6955_H
