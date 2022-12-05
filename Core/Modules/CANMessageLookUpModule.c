/*
 * CANMessageLookUpModule.c
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */

#include "CANMessageLookUpModule.h"


/*********************************************************************************
 *
 * 		Look up table for CAN ID and meta data about its payload
 *
 **********************************************************************************/
const ICommsMessageInfo ICommsMessageLookUpTable[NUMBER_CAN_MESSAGE_IDS] =
	{
			// Message Index			CAN ID		Num of Bytes
			{THROTTLE_DATA_ID,			0x0001, 			2},
			{SPEED_DATA_ID,				0x0400,				2},
			{MOTOR_TEMPERATURE_ID, 		0x0401,				2}
	};
