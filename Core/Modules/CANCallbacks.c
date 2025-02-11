#include "ApplicationTypes.h"

#include "CANMessageLookUpModule.h"
#include "DataAggregation.h"
#include "InternalCommsModule.h"
#include "CANDriver.h"

void ErrorDataCallback(iCommsMessage_t *msg) {
    DebugPrint("ErrorDataCallback! %d", msg->standardMessageID);

    // TODO: Read error codes
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
                // TODO: This could be moved into the voltage callback
        	SystemSetUndervoltage(status);
        case BRAKES_ENABLED:
            DebugPrint("Brakes enabled: %d", status);
        case THROTTLE_TOO_HIGH:
            SystemSetThrottleTooHigh(status);
            break;
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

void PressureTemperatureDataCallback(iCommsMessage_t* msg) {}
void EfficiencyDataCallback(iCommsMessage_t* msg) {}
void ThrottleDataCallback(iCommsMessage_t* msg) {}
void LightsDataCallback(iCommsMessage_t* msg) {}