/*
 * DataAggregation.h
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */

#ifndef MODULES_DATAAGGREGATION_H_
#define MODULES_DATAAGGREGATION_H_

#include "ApplicationTypes.h"

typedef enum ClockState {
    CLOCK_WAITING,  // Waiting to start counting
    CLOCK_COUNTING, // Counting the time
    CLOCK_PAUSED    // Paused, waiting to reset
} ClockState;

typedef union {
    uint32_t all;
    struct {
        ClockState clockState : 2;
        flag_status_t throttleTooHigh : 1;
        flag_status_t motorInitializing : 1;
        flag_status_t undervoltage: 1;
        flag_status_t driverEnabled: 1;
    };
} Events_t;

typedef struct {
    speed_t speed;
    throttle_raw_t throttle;
    ms_t runTime;
} SystemData_t;

typedef enum {
    ScreenVoltage,
    ScreenRPM,
    ScreenSpeed
} ScreenState;

void InitDataAggregator();

speed_t SystemGetSpeed();
throttle_raw_t SystemGetThrottleRaw();
percentage_t SystemGetThrottlePercentage();
voltage_t SystemGetBatteryVoltage();
ms_t SystemGetRunTime();
seconds_t SystemGetRunTimeSeconds();
ClockState SystemGetClockState();
flag_status_t SystemGetThrottleTooHigh();
flag_status_t SystemGetMotorInitializing();
int32_t SystemGetMotorRPM();
flag_status_t SystemGetUndervoltage();
flag_status_t SystemGetDriverEnabled();

uint8_t SystemGetLap();

void SystemSetSpeed(speed_t speed);
void SystemSetThrottleRaw(throttle_raw_t throttleRaw);
void SystemSetBatteryVoltage(voltage_t voltage);
void SystemClearRunTime();
void SystemIncrementRunTime(ms_t time);
void SystemSetClockState(ClockState state);
void SystemSetThrottleTooHigh(flag_status_t state);
void SystemSetMotorInitializing(flag_status_t state);
void SystemSetMotorRPM(int32_t r);
void SystemSetUndervoltage(flag_status_t state);
void SystemSetDriverEnabled(flag_status_t enabled);

void SystemIncrementLap();

void SystemSetLightsTurningLeft(flag_status_t enabled);
void SystemSetLightsTurningRight(flag_status_t enabled);
void SystemSetLightsTurningHazards(flag_status_t enabled);
void SystemSetLightsTurningHeadLights(flag_status_t enabled);
void SystemSetLightsLowBeams(flag_status_t enabled);

void SystemSetScreenState(ScreenState state);
ScreenState SystemGetScreenState();

lights_status_t SystemGetLightsStatus();

#endif /* MODULES_DATAAGGREGATION_H_ */
