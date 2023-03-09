/*
 * DataAggregation.h
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */

#ifndef MODULES_DATAAGGREGATION_H_
#define MODULES_DATAAGGREGATION_H_

#include "ApplicationTypes.h"

typedef enum {Clear = 0, Set = 1} flag_status_t;

typedef enum ClockState
{
	CLOCK_WAITING, // Waiting to start counting
	CLOCK_COUNTING, // Counting the time
	CLOCK_PAUSED // Paused, waiting to reset
} ClockState;

typedef union
{
	uint32_t all;
	struct
	{
		uint32_t hazardSignal;
		ClockState clockState;
	};
} Events_t;

typedef struct
{
	speed_t speed;
	throttle_raw_t throttle;
	ms_t runTime;
} SystemData_t;

void InitDataAggregator();

speed_t SystemGetSpeed();
throttle_raw_t SystemGetThrottleRaw();
percentage_t SystemGetThrottlePercentage();
ms_t SystemGetRunTime();
seconds_t SystemGetRunTimeSeconds();
flag_status_t SystemGetHazardSignal();
ClockState SystemGetClockState();

void SystemSetSpeed(speed_t speed);
void SystemSetThrottleRaw(throttle_raw_t throttleRaw);
void SystemClearRunTime();
void SystemIncrementRunTime(ms_t time);
void SystemSetHazardSignal(flag_status_t status);
void SystemToggleHazardSignal();
void SystemSetClockState(ClockState state);

#endif /* MODULES_DATAAGGREGATION_H_ */
