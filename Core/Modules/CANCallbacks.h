#include "ApplicationTypes.h"

#include "CANMessageLookUpModule.h"

#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

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