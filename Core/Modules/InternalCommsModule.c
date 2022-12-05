/*
 * InternalCommsModule.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *
 *  This is the module for processing information from the cars intercommunication system
 *  Can only import interface files
 */

#include <InternalCommsModule.h>

/***********************************************************
 *
 * 	ICOMMS_DRIVER_INITIALIZE(...)
 *
 * 	This function initializes the car's internal communications
 *
 *	Arguments:
 *	None
 *
 * 	Returns:
 * 	- 1 if initialization successful
 * 	- 0 if initialization failed
 *
 ************************************************************/
#define ICOMMS_DRIVER_INITIALIZE(...) CANSPI_Initialize(__VA_ARGS__)

/***********************************************************
 *
 * 	ICOMMS_DRIVER_MESSAGE_AVAILABLE(...)
 *
 * 	This function checks whether there are messages
 *	ready to be read from the car's internal communications
 *
 *	Arguments:
 *	None
 *
 * 	Returns:
 * 	- 1 if message is available
 * 	- 0 if no message is available
 *
 ************************************************************/
#define ICOMMS_DRIVER_MESSAGE_AVAILABLE(...) CANSPI_messagesInBuffer(__VA_ARGS__)

/***********************************************************
 *
 * 	ICOMMS_DRIVER_TRANSMIT_MESSAGE(...)
 *
 * 	This function transmits a message over the car's communication
 *
 *	Arguments:
 *	uCAN_MSG pointer
 *
 * 	Returns:
 * 	- 1 if message was sent
 * 	- 0 if messages was not able to be sent
 *
 ************************************************************/
#define ICOMMS_DRIVER_TRANSMIT_MESSAGE(...) CANSPI_Transmit(__VA_ARGS__)

/***********************************************************
 *
 * 	ICOMMS_DRIVER_RECEIVE_MESSAGE(...)
 *
 * 	This function receives a message over the car's communication
 *
 *	Arguments:
 *	uCAN_MSG pointer
 *
 * 	Returns:
 * 	- 1 if message was retrieved
 * 	- 0 if no message was retrieved
 *
 ************************************************************/
#define ICOMMS_DRIVER_RECEIVE_MESSAGE(...) CANSPI_Receive(__VA_ARGS__)

PUBLIC result_t ICommsInit()
{
	result_t ret = ICOMMS_DRIVER_INITIALIZE();
	return ret;
}
PUBLIC uint8_t ICommsMessageAvailable()
{
	uint8_t numberOfMsgs = ICOMMS_DRIVER_MESSAGE_AVAILABLE();
	return numberOfMsgs;
}
PUBLIC result_t ICommsTransmit(iCommsMessage_t * txMsg)
{
	result_t ret = ICOMMS_DRIVER_TRANSMIT_MESSAGE(txMsg);
	return ret;
}
PUBLIC result_t ICommsReceive(iCommsMessage_t * rxMsg)
{
	result_t ret = ICOMMS_DRIVER_RECEIVE_MESSAGE(rxMsg);
	return ret;
}

/*********************************************************************************
 *
 * 		Circular queue for messages
 *
 **********************************************************************************/
void iCommMessageQueue_init( iCommsMessageQueue_t * q )
{
	q->head = 0;
	q->count = 0;
	q->tail = 0;
}

void iCommMessageQueue_enqueue( iCommsMessageQueue_t * q, iCommsMessage_t * returnValue )
{
	if(q->count < QUEUE_MAX)
	{
		q->data[q->tail] = *returnValue;
		q->count ++;
		q->tail = q->count % QUEUE_MAX;
	}
}

void iCommMessageQueue_dequeue( iCommsMessageQueue_t * q, iCommsMessage_t * value )
{
	if(q->count > 0)
	{
		*value = q->data[q->head];
		q->count --;
		q->head = (q->head + 1) % QUEUE_MAX;
	}
}

