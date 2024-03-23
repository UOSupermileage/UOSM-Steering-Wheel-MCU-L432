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

#define STACK_SIZE 128*4
#define INTERNAL_COMMS_TASK_PRIORITY (osPriority_t) osPriorityRealtime
#define TIMER_INTERNAL_COMMS_TASK 200UL

#define THROTTLE_RATE 4
#define DRIVER_RATE 2
#define NEW_LAP_RATE 5


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

	const ICommsMessageInfo* eventInfo = CANMessageLookUpGetInfo(EVENT_DATA_ID);
	uint8_t driverTxCounter = 0;

        uint8_t lapTxCounter = 0;

        flag_status_t ledOn = Clear;

	IComms_Init();
	for(;;)
	{
		cycleTick += TIMER_INTERNAL_COMMS_TASK;
		osDelayUntil(cycleTick);

                ledOn = !ledOn;
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, ledOn ? GPIO_PIN_SET : GPIO_PIN_RESET);

		throttleTxCounter++;
		if (throttleTxCounter == THROTTLE_RATE) {
			DebugPrint("%s Sending Throttle!", ICT_TAG);
			iCommsMessage_t throttleTxMsg = IComms_CreatePercentageMessage(throttleInfo->messageID, SystemGetThrottlePercentage());
			result_t r = IComms_Transmit(&throttleTxMsg);
			DebugPrint("%s Sending Throttle! [Result = %d]", ICT_TAG, r);
			throttleTxCounter = 0;
		}

		driverTxCounter++;
		if (driverTxCounter == DRIVER_RATE) {
			DebugPrint("%s Sending Driver = %d!", ICT_TAG, SystemGetDriverEnabled());
			iCommsMessage_t driverTxMsg = IComms_CreateEventMessage(eventInfo->messageID, DRIVER_ENABLED, SystemGetDriverEnabled());
			result_t r = IComms_Transmit(&driverTxMsg);
			driverTxCounter = 0;
		}

                lapTxCounter++;
                if (lapTxCounter == NEW_LAP_RATE) {
                    if (SystemGetNewLap() == Set) {
                        DebugPrint("Sending New Lap");
                        iCommsMessage_t lapTxMsg = IComms_CreateEventMessage(eventInfo->messageID, NEW_LAP, 1);
                        result_t r = IComms_Transmit(&lapTxMsg);
                        SystemSetNewLap(Clear);
                    }

                    lapTxCounter = 0;
                }

		IComms_PeriodicReceive();
	}
}
