/*
 * InternalCommsTask.c
 *
 *  Created on: Sep 10, 2022
 *      Author: mingy
 */

#include "InternalCommsModule.h"
#include "InternalCommsTask.h"
#include "SerialDebugDriver.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*8
#define INTERNAL_COMMS_TASK_PRIORITY (osPriority_t) osPriorityRealtime
#define TIMER_INTERNAL_COMMS_TASK 50UL

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
	ICommsInit();
	uint8_t testTxCounter = 0;
	for(;;)
	{
		cycleTick += TIMER_INTERNAL_COMMS_TASK;
		osDelayUntil(cycleTick);
		DebugPrint("icomms loop");

		iCommsMessage_t txMsg, rxMsg;
		txMsg.standardMessageID = 0x0F;
		txMsg.dataLength = 4;
		txMsg.data[0] = 1;
		txMsg.data[1] = 2;
		txMsg.data[2] = 3;
		txMsg.data[3] = 4;
		/*txMsg.data[4] = 5;
		txMsg.data[5] = 6;
		txMsg.data[6] = 7;
		txMsg.data[7] = 8;*/
		testTxCounter++;
		if(testTxCounter == 25)
		{
			ICommsTransmit(&txMsg);
			testTxCounter =0;
		}


		if(ICommsMessageAvailable()>0)
		{
			ICommsReceive(&rxMsg);
			DebugPrint("Standard ID: %d", rxMsg.standardMessageID);
			DebugPrint("DLC: %d", rxMsg.dataLength);
			for(uint8_t i=0; i<rxMsg.dataLength; i++) DebugPrint("Data[%d]: %d", i, rxMsg.data[i]);
		}

	}
}
