/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Low_Beams_Input_Pin GPIO_PIN_0
#define Low_Beams_Input_GPIO_Port GPIOA
#define High_Beams_Input_Pin GPIO_PIN_2
#define High_Beams_Input_GPIO_Port GPIOA
#define Timer_Input_Pin GPIO_PIN_3
#define Timer_Input_GPIO_Port GPIOA
#define Timer_Input_EXTI_IRQn EXTI3_IRQn
#define Throttle_ADC_Pin GPIO_PIN_4
#define Throttle_ADC_GPIO_Port GPIOA
#define CAN_CS_Pin GPIO_PIN_0
#define CAN_CS_GPIO_Port GPIOB
#define Hazards_Input_Pin GPIO_PIN_1
#define Hazards_Input_GPIO_Port GPIOB
#define Seven_Segs_Pin GPIO_PIN_9
#define Seven_Segs_GPIO_Port GPIOA
#define Seven_SegsA10_Pin GPIO_PIN_10
#define Seven_SegsA10_GPIO_Port GPIOA
#define Extra_Momentary_Input_Pin GPIO_PIN_11
#define Extra_Momentary_Input_GPIO_Port GPIOA
#define Extra_Momentary_Input_EXTI_IRQn EXTI15_10_IRQn
#define EncoderA_Pin GPIO_PIN_12
#define EncoderA_GPIO_Port GPIOA
#define EncoderA_EXTI_IRQn EXTI15_10_IRQn
#define GREEN_LED_Pin GPIO_PIN_3
#define GREEN_LED_GPIO_Port GPIOB
#define Turn_Signal_Left_Input_Pin GPIO_PIN_4
#define Turn_Signal_Left_Input_GPIO_Port GPIOB
#define Turn_Signal_Right_Input_Pin GPIO_PIN_5
#define Turn_Signal_Right_Input_GPIO_Port GPIOB
#define EncoderB_Pin GPIO_PIN_7
#define EncoderB_GPIO_Port GPIOB
#define EncoderB_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
