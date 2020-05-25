/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OUT_00_Pin GPIO_PIN_0
#define OUT_00_GPIO_Port GPIOC
#define OUT_01_Pin GPIO_PIN_1
#define OUT_01_GPIO_Port GPIOC
#define OUT_02_Pin GPIO_PIN_2
#define OUT_02_GPIO_Port GPIOC
#define OUT_03_Pin GPIO_PIN_3
#define OUT_03_GPIO_Port GPIOC
#define LED_NUMLOCK_Pin GPIO_PIN_0
#define LED_NUMLOCK_GPIO_Port GPIOA
#define LED_CAPSLOCK_Pin GPIO_PIN_1
#define LED_CAPSLOCK_GPIO_Port GPIOA
#define LED_SCRLOCK_Pin GPIO_PIN_2
#define LED_SCRLOCK_GPIO_Port GPIOA
#define OUT_04_Pin GPIO_PIN_4
#define OUT_04_GPIO_Port GPIOC
#define OUT_05_Pin GPIO_PIN_5
#define OUT_05_GPIO_Port GPIOC
#define IN_00_Pin GPIO_PIN_0
#define IN_00_GPIO_Port GPIOB
#define IN_01_Pin GPIO_PIN_1
#define IN_01_GPIO_Port GPIOB
#define IN_02_Pin GPIO_PIN_2
#define IN_02_GPIO_Port GPIOB
#define IN_10_Pin GPIO_PIN_10
#define IN_10_GPIO_Port GPIOB
#define IN_11_Pin GPIO_PIN_11
#define IN_11_GPIO_Port GPIOB
#define IN_12_Pin GPIO_PIN_12
#define IN_12_GPIO_Port GPIOB
#define IN_13_Pin GPIO_PIN_13
#define IN_13_GPIO_Port GPIOB
#define IN_14_Pin GPIO_PIN_14
#define IN_14_GPIO_Port GPIOB
#define IN_15_Pin GPIO_PIN_15
#define IN_15_GPIO_Port GPIOB
#define OUT_06_Pin GPIO_PIN_6
#define OUT_06_GPIO_Port GPIOC
#define OUT_07_Pin GPIO_PIN_7
#define OUT_07_GPIO_Port GPIOC
#define IN_03_Pin GPIO_PIN_3
#define IN_03_GPIO_Port GPIOB
#define IN_04_Pin GPIO_PIN_4
#define IN_04_GPIO_Port GPIOB
#define IN_05_Pin GPIO_PIN_5
#define IN_05_GPIO_Port GPIOB
#define IN_06_Pin GPIO_PIN_6
#define IN_06_GPIO_Port GPIOB
#define IN_07_Pin GPIO_PIN_7
#define IN_07_GPIO_Port GPIOB
#define IN_08_Pin GPIO_PIN_8
#define IN_08_GPIO_Port GPIOB
#define IN_09_Pin GPIO_PIN_9
#define IN_09_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
