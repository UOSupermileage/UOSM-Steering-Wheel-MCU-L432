/*
 * InternalCommsTask.c
 *
 *  Created on: Sep 10, 2022
 *      Author: mingy
 */


//#include "CANMessageLookUpModule.h"
#include "InternalCommsTask.h"
#include "InternalCommsModule.h"
#include "CANMessageLookUpModule.h"
#include "DataAggregation.h"

#define STACK_SIZE 128*8
#define INTERNAL_COMMS_TASK_PRIORITY (osPriority_t) osPriorityRealtime
#define TIMER_INTERNAL_COMMS_TASK 200UL

#define THROTTLE_RATE 4
#define SPEED_RATE 4

const char ICT_TAG[] = "#ICT:";

PUBLIC void InitInternalCommsTask(void);
PRIVATE void InternalCommsTask(void *argument);

osThreadId_t InternalCommsTaskHandle;
const osThreadAttr_t InternalCommsTask_attributes = {
	.name = "InternalCommunications",
	.stack_size = STACK_SIZE,
	.priority = INTERNAL_COMMS_TASK_PRIORITY,
};

PUBLIC void InitInternalCommsTask(void)
{

	InternalCommsTaskHandle = osThreadNew(InternalCommsTask, NULL, &InternalCommsTask_attributes);

}
PRIVATE void InternalCommsTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("icomms");

	const ICommsMessageInfo* throttleInfo = CANMessageLookUpGetInfo(THROTTLE_DATA_ID);
	uint8_t throttleTxCounter = 0;

	const ICommsMessageInfo* speedInfo = CANMessageLookUpGetInfo(SPEED_DATA_ID);
	uint8_t speedTxCounter = 0;

	IComms_Init();
	for(;;)
	{
		cycleTick += TIMER_INTERNAL_COMMS_TASK;
		osDelayUntil(cycleTick);

		throttleTxCounter++;
		if (throttleTxCounter == THROTTLE_RATE) {
			DebugPrint("%s Sending Throttle!", ICT_TAG);
			iCommsMessage_t throttleTxMsg = IComms_CreatePercentageMessage(throttleInfo->messageID, SystemGetThrottlePercentage());
			result_t r = IComms_Transmit(&throttleTxMsg);
			DebugPrint("%s Sending Throttle! [Result = %d]", ICT_TAG, r);
			throttleTxCounter = 0;
		}

		speedTxCounter++;
		if (speedTxCounter == SPEED_RATE) {
			DebugPrint("%s Sending Speed!", ICT_TAG);
			iCommsMessage_t speedTxMsg = IComms_Create32BitMessage(speedInfo->messageID, SystemGetSpeed());
			result_t r = IComms_Transmit(&speedTxMsg);
			DebugPrint("%s Sending Speed! [Result = %d]", ICT_TAG, r);
			speedTxCounter = 0;
		}

		IComms_PeriodicReceive();
	}
}
