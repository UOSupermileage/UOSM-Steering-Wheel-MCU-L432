/*
 * DataAggregation.h
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */

#ifndef MODULES_DATAAGGREGATION_H_
#define MODULES_DATAAGGREGATION_H_

#include "ApplicationTypes.h"

typedef enum {Set, Clear} flag_status_t;
typedef union
{
	uint32_t all;
	struct
	{
		uint32_t rightSignal;
		uint32_t leftSignal;
		uint32_t hazardSignal;
		uint32_t timerStart;
		uint32_t timerStop;
	};
}Events_t;

typedef struct
{
	throttle_raw_t throttle;
} SystemData_t;

void InitDataAggregator();

speed_t SystemGetSpeed();
throttle_raw_t SystemGetThrottleRaw();
percentage_t SystemGetThrottlePercentage();
flag_status_t SystemGetRightSignal();
flag_status_t SystemGetLeftSignal();
flag_status_t SystemGetHazardSignal();
flag_status_t SystemGetTimerStart();
flag_status_t SystemGetTimerStop();

void SystemSetThrottleRaw(throttle_raw_t throttleRaw);
void SystemSetRightSignal(flag_status_t status);
void SystemSetLeftSignal(flag_status_t status);
void SystemSetHazardSignal(flag_status_t status);
void SystemSetTimerStart(flag_status_t status);
void SystemSetTimerStop(flag_status_t status);

#endif /* MODULES_DATAAGGREGATION_H_ */
