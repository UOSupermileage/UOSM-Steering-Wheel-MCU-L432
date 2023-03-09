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
      uint32_t hall_capture = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
      uint32_t delta_capture = hall_capture - last_capture;
      last_capture = hall_capture;
      frequency = HAL_RCC_GetPCLK1Freq() / (htim1.Init.Prescaler + 1) / delta_capture;
      __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_CC1);
    }
  }
}

PUBLIC speed_t HallGetSpeed() {
	return (frequency * 3600 * HALL_CIRC) / (HALL_BOLTS * 1000);
}
