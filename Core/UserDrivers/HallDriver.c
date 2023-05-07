/*
 * HallDriver.c
 *
 *  Created on: Jan. 23, 2023
 *      Author: jeremycote
 *
 *  See article:
 *  https://deepbluembedded.com/stm32-input-capture-frequency-measurement-example-timer-input-capture-mode/
 */

#include "HallDriver.h"
#include "DataAggregation.h"

extern TIM_HandleTypeDef htim1;

#define IDLE 0
#define DONE 1
#define F_CLK 64000000UL
#define COUNTER_SIZE 65536

volatile uint8_t state = IDLE;
volatile uint32_t time1 = 0;
volatile uint32_t time2 = 0;
volatile uint32_t nTicks = 0;
volatile uint16_t overflowCounter = 0;
volatile uint32_t frequency = 0;

PUBLIC void HallInit() {
    DebugPrint("Init HallDriver");
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
}

PUBLIC speed_t HallGetSpeed() { return (frequency * 3600 * HALL_CIRC) / (HALL_BOLTS * 1000); }

PUBLIC void HallPeriodElapsedCallback(TIM_HandleTypeDef *htim) { overflowCounter++; }

PUBLIC void HallCaptureCallback(TIM_HandleTypeDef *htim) {
    if (state == IDLE) {
        time1 = TIM2->CCR1;
        overflowCounter = 0;
        state = DONE;
    } else if (state == DONE) {
        time2 = TIM2->CCR1;
        nTicks = (time2 + (overflowCounter * COUNTER_SIZE)) - time1;
        frequency = (uint32_t)(F_CLK / nTicks);
        state = IDLE;
    }
}
