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
#define LIGHTS_RATE 2


const char ICT_TAG[] = "#ICT:";

void InitInternalCommsTask(void);
void InternalCommsTask(void *argument);

osThreadId_t InternalCommsTaskHandle;
const osThreadAttr_t InternalCommsTask_attributes = {
	.name = "InternalCommunications",
	.stack_size = STACK_SIZE,
	.priority = INTERNAL_COMMS_TASK_PRIORITY,
};

void InitInternalCommsTask(void)
{

	InternalCommsTaskHandle = osThreadNew(InternalCommsTask, NULL, &InternalCommsTask_attributes);

}
void InternalCommsTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("icomms");

	const ICommsMessageInfo* throttleInfo = CANMessageLookUpGetInfo(THROTTLE_DATA_ID);
	uint8_t throttleTxCounter = 0;

	const ICommsMessageInfo* eventInfo = CANMessageLookUpGetInfo(EVENT_DATA_ID);
	uint8_t driverTxCounter = 0;

        const ICommsMessageInfo* lightsInfo = CANMessageLookUpGetInfo(LIGHT_DATA_ID);
        uint8_t lightsTxCounter = 0;

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
			iCommsMessage_t throttleTxMsg = IComms_CreatePercentageMessage(THROTTLE_DATA_ID, SystemGetThrottlePercentage());
			result_t r = IComms_Transmit(&throttleTxMsg);
			DebugPrint("%s Sending Throttle! [Result = %d]", ICT_TAG, r);
			throttleTxCounter = 0;
		}

		driverTxCounter++;
		if (driverTxCounter == DRIVER_RATE) {
			DebugPrint("%s Sending Driver = %d!", ICT_TAG, SystemGetDriverEnabled());
			iCommsMessage_t driverTxMsg = IComms_CreateEventMessage(DRIVER_ENABLED, SystemGetDriverEnabled());
			result_t r = IComms_Transmit(&driverTxMsg);
			driverTxCounter = 0;
		}

                lapTxCounter++;
                if (lapTxCounter == NEW_LAP_RATE) {
                    DebugPrint("Sending New Lap");
                    iCommsMessage_t lapTxMsg = IComms_CreateEventMessage(NEW_LAP, SystemGetLap());
                    result_t r = IComms_Transmit(&lapTxMsg);
                    lapTxCounter = 0;
                }

                lightsTxCounter++;
                if (lightsTxCounter == LIGHTS_RATE) {
                    DebugPrint("Sending New Lights %04x", SystemGetLightsStatus().all);
                    iCommsMessage_t lightsTxMsg = IComms_CreateLightsMessage(SystemGetLightsStatus());
                    result_t r = IComms_Transmit(&lightsTxMsg);
                    lightsTxCounter = 0;
                }

		IComms_PeriodicReceive();
	}
}
