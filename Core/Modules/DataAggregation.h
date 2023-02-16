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

typedef union
{
	uint32_t all;
	struct
	{
		uint32_t hazardSignal;
		uint32_t timerRunning;
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
flag_status_t SystemGetTimerRunning();

void SystemSetSpeed(speed_t speed);
void SystemSetThrottleRaw(throttle_raw_t throttleRaw);
void SystemClearRunTime();
void SystemIncrementRunTime(ms_t time);
void SystemSetHazardSignal(flag_status_t status);
void SystemToggleHazardSignal();
void SystemSetTimerRunning(flag_status_t status);

#endif /* MODULES_DATAAGGREGATION_H_ */
