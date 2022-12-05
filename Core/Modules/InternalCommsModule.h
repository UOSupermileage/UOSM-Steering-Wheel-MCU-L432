/*
 * InternalCommsModule.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef MODULES_INTERNALCOMMSMODULE_H_
#define MODULES_INTERNALCOMMSMODULE_H_

#include <CANDriver.h>
#include <ApplicationTypes.h>

PUBLIC result_t ICommsInit();
PUBLIC uint8_t ICommsMessageAvailable();
PUBLIC result_t ICommsTransmit(iCommsMessage_t * txMsg);
PUBLIC result_t ICommsReceive(iCommsMessage_t * rxMsg);

// Circular Queue
#define QUEUE_MAX 16
typedef struct iCommsMessageQueue_t
{
	uint32_t head;
	uint32_t tail;
	uint32_t count;
	iCommsMessage_t data[QUEUE_MAX];
}iCommsMessageQueue_t;

/********************************
 * Forward declarations
 ********************************/
PRIVATE void iCommsMessageQueue_init(iCommsMessageQueue_t * q);
PRIVATE void iCommsMessageQueue_dequeue(iCommsMessageQueue_t * q, iCommsMessage_t * returnValue);
PRIVATE void iCommsMessageQueue_enqueue(iCommsMessageQueue_t * q, iCommsMessage_t value);

PUBLIC void IComms_AddMessageToSend(uint8_t * data, length_t len, uint16_t canID);


#endif /* MODULES_INTERNALCOMMSMODULE_H_ */
