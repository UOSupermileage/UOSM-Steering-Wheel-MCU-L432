#include "ApplicationTypes.h"

#include "CANMessageLookUpModule.h"
#include "DataAggregation.h"
#include "InternalCommsModule.h"
#include "CANDriver.h"

void ErrorDataCallback(iCommsMessage_t *msg) {
    DebugPrint("ErrorDataCallback! %d", msg->standardMessageID);

    if (msg->dataLength == CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes) {
        ErrorCode code = msg->data[1];
        flag_status_t status = msg->data[0];

        DebugPrint("ErrorDataCallback, received code %d with status %d", code, status);
        switch (code) {
        case THROTTLE_TOO_HIGH:
            SystemSetThrottleTooHigh(status);
            break;
        }
    } else {
        DebugPrint("msg.dataLength does not match lookup table. %d != %d", msg->dataLength, CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes);
    }
}

void EventDataCallback(iCommsMessage_t *msg) {
    DebugPrint("EventDataCallback! %d", msg->standardMessageID);

    if (msg->dataLength == CANMessageLookUpTable[EVENT_DATA_ID].numberOfBytes) {
        EventCode code = msg->data[1];
        flag_status_t status = msg->data[0];

        DebugPrint("EventDataCallback, received code %d with status %d", code, status);
        switch (code) {
        case MOTOR_INITIALIZING:
            SystemSetMotorInitializing(status);
            break;
        case UNDERVOLTAGE:
        	SystemSetUndervoltage(status);
        default:
            break;
        }
    } else {
        DebugPrint("msg.dataLength does not match lookup table. %d != %d", msg->dataLength, CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes);
    }
}

void MotorRPMDataCallback(iCommsMessage_t* msg) {
	int32_t rpm = readMsg(msg);
	DebugPrint("CAN rpm received: %d", rpm);
	SystemSetMotorRPM(rpm);
}

void CurrentVoltageDataCallback(iCommsMessage_t* msg) {

        uint16_pair_t pair = readMsgPairUInt16Bit(msg);

        DebugPrint("CAN current received: %d", pair.a);
	DebugPrint("CAN voltage received: %d", pair.b);
	SystemSetBatteryVoltage(pair.b);
}

void SpeedDataCallback(iCommsMessage_t *msg) {
    uint32_t speed = readMsg(msg);
    DebugPrint("CAN speed received: %d", speed);
    SystemSetSpeed(speed);
}

void ThrottleDataCallback(iCommsMessage_t *msg) { DebugPrint("ThrottleDataCallback not implemented! %d", msg->standardMessageID); }
void PressureDataCallback(iCommsMessage_t *msg) { DebugPrint("SpeedDataCallback not implemented! %d", msg->standardMessageID); }
void TemperatureDataCallback(iCommsMessage_t *msg) { DebugPrint("SpeedDataCallback not implemented! %d", msg->standardMessageID); }
