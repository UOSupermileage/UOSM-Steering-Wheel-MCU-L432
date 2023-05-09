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
#include "InteruptModule.h"

extern TIM_HandleTypeDef htim1;

#define IDLE 0
#define DONE 1
#define F_CLK 32000000 / 12000
#define COUNTER_SIZE 65536

volatile uint8_t state = IDLE;
volatile uint32_t time1 = 0;
volatile uint32_t time2 = 0;
volatile uint32_t nTicks = 0;
volatile uint32_t hallFrequency = 0;

volatile uint32_t lastSample;

PUBLIC void HallInit() {
    DebugPrint("Init HallDriver");
    InteruptRegisterCallback(INTERUPT_GPIO_8_ID, HallCaptureCallback, 0);
}

PUBLIC speed_t HallGetSpeed() {
	return (hallFrequency * 36 * HALL_CIRC) / (HALL_BOLTS);
}

PUBLIC void HallCaptureCallback() {
    if (state == IDLE) {
        time1 = osKernelGetTickCount();//TIM1->CCR1;
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
