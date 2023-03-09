/*
 * HallDriver.c
 *
 *  Created on: Jan. 23, 2023
 *      Author: jeremycote
 */

#include "HallDriver.h"
#include "DataAggregation.h"
#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

extern TIM_HandleTypeDef htim1;

uint32_t last_capture = 0;
uint32_t frequency = 0;

PUBLIC void HallInit() {
	DebugPrint("Init HallDriver");
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
}

void HallIRQHandler(void)
{
  if(__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_CC1) != RESET)
  {
    if(__HAL_TIM_GET_IT_SOURCE(&htim1, TIM_IT_CC1) != RESET)
    {
    	DebugPrint("Triggered IRQ");
      uint32_t hall_capture = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
      uint32_t delta_capture = hall_capture - last_capture;
      last_capture = hall_capture;
      frequency = HAL_RCC_GetPCLK1Freq() / (htim1.Init.Prescaler + 1) / delta_capture;
      __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_CC1);
    }
  }
}

PUBLIC speed_t HallGetSpeed() {
	DebugPrint("Current frequency: %d", frequency);
	return (frequency * 60 * HALL_CIRC) / (HALL_BOLTS * 1000);
}


//
//static uint32_t milisecondsPerRevolution = 0;
//static uint32_t lastHallTick = 0;
//
//PUBLIC void HallPeriodicJob() {
//
//	// tick ++  ## Assuming negative edge
//	// time = 0
//	// timeout = 0
//	// while (time < debounceThresh and timeout < timeoutThresh):
//	//    if (sensorEXTI): time = 0
//	//    time += timedelta
//	//    timeout += timedelta
//
//	// TODO: What happens when tick overflows and goes back to 0?
//	milisecondsPerRevolution = (osKernelGetTickCount() - lastHallTick) * HALL_BOLTS;
//	lastHallTick = osKernelGetTickCount();
//}
//
//PUBLIC result_t HallConvertSpeed() {
//
//
//	DebugPrint("Miliseconds Per Revolution: %d", milisecondsPerRevolution);
//
//	DebugPrint("RPM: [%d]", 60000/(milisecondsPerRevolution));
//
//	//Angular velocity in radians/second.
//	speed_t speed = 60000/milisecondsPerRevolution * HALL_CIRC * 60 / 1000 ;
//
//	SystemSetSpeed(speed);
//
//	return RESULT_OK;
//}
