/*
 * HallDriver.c
 *
 *  Created on: Jan. 23, 2023
 *      Author: jeremycote
 *
 *  See article:
 *  https://deepbluembedded.com/stm32-input-capture-hallFrequency-measurement-example-timer-input-capture-mode/
 */

#include "HallDriver.h"
#include "DataAggregation.h"

extern TIM_HandleTypeDef htim1;

#define IDLE 0
#define DONE 1
#define F_CLK 32000000 / 12000
#define COUNTER_SIZE 65536

volatile uint8_t state = IDLE;
volatile uint32_t time1 = 0;
volatile uint32_t time2 = 0;
volatile uint32_t nTicks = 0;
volatile uint16_t overflowCounter = 0;
volatile uint32_t hallFrequency = 0;

volatile uint32_t lastSample;

PUBLIC void HallInit() {
    DebugPrint("Init HallDriver");
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
}

PUBLIC speed_t HallGetSpeed() {

//	uint32_t t = osKernelGetTickCount();
//	if (t > lastSample && t - lastSample > 2000) {
//		hallFrequency = 0;
//	}
	DebugPrint("Time1: %d, Time2: %d, overflowCounter: %d", time1, time2, overflowCounter);

	return (hallFrequency * 36 * HALL_CIRC) / (HALL_BOLTS);
}

PUBLIC void HallPeriodElapsedCallback(TIM_HandleTypeDef *htim) { overflowCounter++; }

PUBLIC void HallCaptureCallback(TIM_HandleTypeDef *htim) {
    if (state == IDLE) {
        time1 = osKernelGetTickCount();//TIM1->CCR1;
        overflowCounter = 0;
        state = DONE;
        return;
    }

    if (state != DONE) {
    	return;
    }

	state = IDLE;

	time2 = osKernelGetTickCount();//TIM1->CCR1;

	if (time2 < time1) {
		DebugPrint("Overflowed");
		return;
	}

	nTicks = time2 - time1;

	if (nTicks == 0) {
		DebugPrint("Div by 0");
		return;
	}

	hallFrequency = (uint32_t)(100 * osKernelGetTickFreq() / nTicks);
}
