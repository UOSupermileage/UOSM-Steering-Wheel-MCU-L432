/*
 * TaskManager.c
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *
 *  This Task manages all other tasks by checking flags and running the appropriate tasks
 */
#include "TaskManager.h"
#include "DataAggregation.h"
#include "ThrottleTask.h"
#include "InternalCommsTask.h"
#include "LightsTask.h"
#include "SegDisplayTask.h"
#include "ClockTask.h"

void RunTaskManager( void )
{
	InitDataAggregator();
	InitThrottleTask();
	InitInternalCommsTask();
	InitLightsTask();
	InitClockTask();
	InitSegDisplayTask();
}
