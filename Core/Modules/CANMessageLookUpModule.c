/*
 * CANMessageLookUpModule.c
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */

#include "CANMessageLookUpModule.h"
#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

const char CLM_TAG[] = "#CLM:";

// Callbacks
void ThrottleDataCallback(iCommsMessage_t msg);
void ErrorDataCallback(iCommsMessage_t msg);
void SpeedDataCallback(iCommsMessage_t msg);
void MotorTemperatureCallback(iCommsMessage_t msg);

/*********************************************************************************
 *
 * 		Look up table for CAN ID and meta data about its payload
 *
 **********************************************************************************/
const ICommsMessageInfo CANMessageLookUpTable[NUMBER_CAN_MESSAGE_IDS] =
	{
			// Message Index			CAN ID		Num of Bytes		Callback
			{THROTTLE_DATA_ID,			0x0001, 			2,		&ThrottleDataCallback},
			{ERROR_DATA_ID,				0x0040,				2,		&ErrorDataCallback},
			{SPEED_DATA_ID,				0x0400,				2,		&SpeedDataCallback},
			{MOTOR_TEMPERATURE_ID, 		0x0401,				2,		&MotorTemperatureCallback}
	};


void ThrottleDataCallback(iCommsMessage_t msg)
{
	DebugPrint("ThrottleDataCallback! %d", msg.standardMessageID);
}
void ErrorDataCallback(iCommsMessage_t msg)
{
	DebugPrint("ErrorDataCallback! %d", msg.standardMessageID);

	if (msg.dataLength == CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes) {
		ErrorCode code = msg.data[1];
		flag_status_t status = msg.data[0];

		DebugPrint("ErrorDataCallback, received code %d with status %d", code, status);
		switch (code) {
		case THROTTLE_TOO_HIGH:
			SystemSetThrottleTooHigh(status);
			break;
		}
	} else {
		DebugPrint("msg.dataLength does not match lookup table. %d != %d", msg.dataLength, CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes);
	}

}
void SpeedDataCallback(iCommsMessage_t msg)
{
	DebugPrint("SpeedDataCallback! %d", msg.standardMessageID);
}
void MotorTemperatureCallback(iCommsMessage_t msg)
{
	DebugPrint("MotorTemperatureCallback! %d", msg.standardMessageID);
}

PUBLIC const ICommsMessageInfo* CANMessageLookUpGetInfo(ICommsMessageLookUpIndex id) {
	return &CANMessageLookUpTable[id];
}
