/*
 * DataAggregation.c
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */
#include "DataAggregation.h"
#include "ADCDriver.h"

// Global Variables
SystemData_t SystemData;
volatile Events_t EventFlags;
int32_t rpm;
voltage_t voltage;
static volatile lights_status_t lights;
static volatile ScreenState screenState = ScreenSpeed;

static volatile uint8_t lapCount = 0;

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

ms_t SystemGetRunTime()
{
	return SystemData.runTime;
}

seconds_t SystemGetRunTimeSeconds()
{
	return SystemData.runTime / 1000;
}

ClockState SystemGetClockState()
{
	return EventFlags.clockState;
}
flag_status_t SystemGetThrottleTooHigh()
{
	return EventFlags.throttleTooHigh;
}
flag_status_t SystemGetMotorInitializing()
{
	return EventFlags.motorInitializing;
}
flag_status_t SystemGetUndervoltage()
{
	return EventFlags.undervoltage;
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
void SystemIncrementRunTime(ms_t time)
{
	SystemData.runTime += time;
}
void SystemSetClockState(ClockState state)
{
	EventFlags.clockState = state;
}
void SystemSetThrottleTooHigh(flag_status_t state)
{
	EventFlags.throttleTooHigh = state;
}
void SystemSetMotorInitializing(flag_status_t state)
{
	EventFlags.motorInitializing = state;
}
void SystemSetUndervoltage(flag_status_t state)
{
	EventFlags.undervoltage = state;
}

voltage_t SystemGetBatteryVoltage() {
	return voltage;
}

uint32_t SystemGetRed() {
	uint32_t i = lights.r;
	return i;
}

uint32_t SystemGetGreen() {
	return lights.g;
}
uint32_t SystemGetBlue() {
	return lights.b;
}

void SystemSetBatteryVoltage(voltage_t v) {
	voltage = v;

        // Undervolt if battery is bellow 44V
	SystemSetUndervoltage(v < 44000 ? Set : Clear);
}

void SystemSetMotorRPM(int32_t r) {
	rpm = r;
}
int32_t SystemGetMotorRPM() {
	return rpm;
}

flag_status_t SystemGetDriverEnabled() {
	return EventFlags.driverEnabled;
}

uint8_t SystemGetLap() {
    return lapCount;
}
void SystemIncrementLap() {
    lapCount += 1;
}

void SystemSetDriverEnabled(flag_status_t enabled) {
	EventFlags.driverEnabled = enabled;
}


void SystemSetLightsTurningLeft(flag_status_t enabled) {
        lights.left_turn_enabled = enabled;
}

void SystemSetLightsTurningRight(flag_status_t enabled) {
        lights.right_turn_enabled = enabled;
}
void SystemSetLightsTurningHazards(flag_status_t enabled) {
        lights.hazards_enabled = enabled;
}
void SystemSetLightsTurningHeadLights(flag_status_t enabled) {
        lights.headlights_enabled = enabled;
}
void SystemSetLightsLowBeams(flag_status_t enabled) {
	lights.low_beams_enabled = enabled;
}

void SystemSetScreenState(ScreenState state) {
    screenState = state;
}

void SystemSetRed(uint32_t red) {
	lights.r = red;
}

void SystemSetGreen(uint32_t green) {
	lights.g = green;
}

void SystemSetBlue(uint32_t blue) {
	lights.b = blue;
}

ScreenState SystemGetScreenState() {
    return screenState;
}

lights_status_t SystemGetLightsStatus() {
        return lights;
}

void InitDataAggregator()
{
	EventFlags.all = 0;
	SystemData.throttle = 0;

	SystemSetMotorInitializing(Set);
}
