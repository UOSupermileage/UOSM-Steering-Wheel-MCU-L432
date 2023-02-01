/*
 * DataAggregation.c
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */
#include "DataAggregation.h"
#include "ADCDriver.h"
#include "HallDriver.h"

// Global Variables
SystemData_t SystemData;
Events_t EventFlags;

speed_t SystemGetSpeed()
{
	return SystemData.speed;
}

throttle_raw_t SystemGetThrottleRaw()
{
	return SystemData.throttle;
}

percentage_t SystemGetThrottlePercentage()
{
	return ADCConvertThrottle(SystemData.throttle);
}

seconds_t SystemGetRunTime()
{
	return SystemData.runTime;
}

flag_status_t SystemGetRightSignal()
{
	return EventFlags.rightSignal;
}
flag_status_t SystemGetLeftSignal()
{
	return EventFlags.leftSignal;
}
flag_status_t SystemGetHazardSignal()
{
	return EventFlags.hazardSignal;
}
flag_status_t SystemGetTimerRunning()
{
	return EventFlags.timerRunning;
}


void SystemSetSpeed(speed_t speed)
{
	SystemData.speed = speed;
}
void SystemSetThrottleRaw(throttle_raw_t throttleRaw)
{
	SystemData.throttle = throttleRaw;
}
void SystemClearRunTime()
{
	SystemData.runTime = 0;
}
void SystemIncrementRunTime(seconds_t time)
{
	SystemData.runTime += time;
}
void SystemSetRightSignal(flag_status_t status)
{
	EventFlags.rightSignal = status;
}
void SystemToggleRightSignal() {
	EventFlags.rightSignal = !EventFlags.rightSignal;
}
void SystemSetLeftSignal(flag_status_t status)
{
	EventFlags.leftSignal = status;
}
void SystemToggleLeftSignal() {
	EventFlags.leftSignal = !EventFlags.leftSignal;
}
void SystemSetHazardSignal(flag_status_t status)
{
	EventFlags.hazardSignal = status;
}
void SystemToggleHazardSignal() {
	EventFlags.hazardSignal = !EventFlags.hazardSignal;
}
void SystemSetTimerRunning(flag_status_t status)
{
	EventFlags.timerRunning = status;
}

void InitDataAggregator()
{
	EventFlags.all = 0;
	SystemData.throttle = 0;
}
