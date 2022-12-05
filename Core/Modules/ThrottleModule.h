/*
 * ThrottleModule.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 */

#ifndef MODULES_THROTTLEMODULE_H_
#define MODULES_THROTTLEMODULE_H_

// Our Libraries
#include "ApplicationTypes.h"
#include "DataAggregation.h"

PUBLIC result_t Throttle_UpdateThrottle();
PUBLIC result_t Throttle_BroadcastThrottleRaw();

#endif /* MODULES_THROTTLEMODULE_H_ */
