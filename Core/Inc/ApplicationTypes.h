/*
 * ApplicationTypes.h
 *
 *	custom data types
 *
 *  Created on: Sep 4, 2022
 *      Author: mingye
 */

#ifndef _APPLICATIONTYPES_H_
#define _APPLICATIONTYPES_H_

#include <stdint.h>

#define PUBLIC
#define PRIVATE

#define PI_T2 6.28318530718      // Pi * 2

typedef enum
{
	RESULT_FAIL,
	RESULT_OK
} result_t;

typedef uint16_t length_t;
typedef uint16_t throttle_raw_t;
typedef uint16_t speed_t;
typedef uint16_t percentage_t;
typedef float km_per_second_t;
typedef uint16_t seconds_t;
typedef uint32_t ms_t;


typedef struct
{
	uint16_t standardMessageID; // 11 bit max
	uint8_t dataLength; // max 8
	uint8_t data[8];
}iCommsMessage_t;


#endif /* _APPLICATIONTYPES_H_ */
