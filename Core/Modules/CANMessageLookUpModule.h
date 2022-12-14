/*
 * CANMessageLookUpModule.h
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */

#ifndef MODULES_CANMESSAGELOOKUPMODULE_H_
#define MODULES_CANMESSAGELOOKUPMODULE_H_

#include "ApplicationTypes.h"


// CAN Message IDs for each piece of data
// Details can be found on the CAN Reference Document
#define NUMBER_CAN_MESSAGE_IDS 3

typedef enum ICommsMessageLookUpIndex
{
	THROTTLE_DATA_ID,
	SPEED_DATA_ID,
	MOTOR_TEMPERATURE_ID
} ICommsMessageLookUpIndex;

typedef uint16_t MessageCANID_t;

typedef struct
{
	ICommsMessageLookUpIndex index;
	MessageCANID_t messageID;
	uint8_t numberOfBytes;

} ICommsMessageInfo;


#endif /* MODULES_CANMESSAGELOOKUPMODULE_H_ */
