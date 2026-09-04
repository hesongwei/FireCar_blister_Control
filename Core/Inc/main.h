/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

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
#define MCU_RELAY_1_Pin GPIO_PIN_7
#define MCU_RELAY_1_GPIO_Port GPIOB
#define MCU_RELAY_2_Pin GPIO_PIN_14
#define MCU_RELAY_2_GPIO_Port GPIOC
#define MCU_RELAY_3_Pin GPIO_PIN_15
#define MCU_RELAY_3_GPIO_Port GPIOC
#define MCU_RELAY_4_Pin GPIO_PIN_0
#define MCU_RELAY_4_GPIO_Port GPIOA
#define MCU_RELAY_5_Pin GPIO_PIN_1
#define MCU_RELAY_5_GPIO_Port GPIOA
#define Limit_Signal1_Pin GPIO_PIN_4
#define Limit_Signal1_GPIO_Port GPIOA
#define Limit_Signal2_Pin GPIO_PIN_5
#define Limit_Signal2_GPIO_Port GPIOA
#define Limit_Signal3_Pin GPIO_PIN_6
#define Limit_Signal3_GPIO_Port GPIOA
#define Limit_Signal4_Pin GPIO_PIN_7
#define Limit_Signal4_GPIO_Port GPIOA
#define Limit_Signal5_Pin GPIO_PIN_0
#define Limit_Signal5_GPIO_Port GPIOB
#define Limit_Signal6_Pin GPIO_PIN_11
#define Limit_Signal6_GPIO_Port GPIOA
#define Run_LED_Pin GPIO_PIN_12
#define Run_LED_GPIO_Port GPIOA
#define MCU_RELAY_6_Pin GPIO_PIN_3
#define MCU_RELAY_6_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
