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
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define CAN_CS_Pin GPIO_PIN_3
#define CAN_CS_GPIO_Port GPIOA
#define Throttle_Pin GPIO_PIN_4
#define Throttle_GPIO_Port GPIOA
#define Timer_Start_Stop_Pin GPIO_PIN_0
#define Timer_Start_Stop_GPIO_Port GPIOB
#define Timer_Start_Stop_EXTI_IRQn EXTI0_IRQn
#define Hazard_Lights_Pin GPIO_PIN_1
#define Hazard_Lights_GPIO_Port GPIOB
#define Hazard_Lights_EXTI_IRQn EXTI1_IRQn
#define Hall_Effect_Pin GPIO_PIN_8
#define Hall_Effect_GPIO_Port GPIOA
#define Hall_Effect_EXTI_IRQn EXTI9_5_IRQn
#define Seven_Segs_Pin GPIO_PIN_9
#define Seven_Segs_GPIO_Port GPIOA
#define Seven_SegsA10_Pin GPIO_PIN_10
#define Seven_SegsA10_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_3
#define LD3_GPIO_Port GPIOB
#define Turn_Signal_Left_Pin GPIO_PIN_4
#define Turn_Signal_Left_GPIO_Port GPIOB
#define Turn_Signal_Left_EXTI_IRQn EXTI4_IRQn
#define Turn_Signal_Right_Pin GPIO_PIN_5
#define Turn_Signal_Right_GPIO_Port GPIOB
#define Turn_Signal_Right_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
