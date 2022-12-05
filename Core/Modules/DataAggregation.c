/*
 * DataAggregation.c
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */
#include "DataAggregation.h"

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
flag_status_t SystemGetTimerStart()
{
	return EventFlags.timerStart;
}
flag_status_t SystemGetTimerStop()
{
	return EventFlags.timerStop;
}

void SystemSetSpeed(speed_t speed)
{
	SystemData.speed = speed;
}
void SystemSetThrottleRaw(throttle_raw_t throttleRaw)
{
	SystemData.throttle = throttleRaw;
}
void SystemSetRightSignal(flag_status_t status)
{
	EventFlags.rightSignal = status;
}
void SystemSetLeftSignal(flag_status_t status)
{
	EventFlags.leftSignal = status;
}
void SystemSetHazardSignal(flag_status_t status)
{
	EventFlags.hazardSignal = status;
}
void SystemSetTimerStart(flag_status_t status)
{
	EventFlags.timerStart = status;
}
void SystemSetTimerStop(flag_status_t status)
{
	EventFlags.timerStop = status;
}

void InitDataAggregator()
{
	EventFlags.all = 0;
	SystemData.speed = 0;
	SystemData.throttle = 0;
}
