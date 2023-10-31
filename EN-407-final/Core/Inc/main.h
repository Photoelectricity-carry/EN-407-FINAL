/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Track.h"
#include "motor.h"
#include "tsc2300.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
int getTIMx_DetaCnt(TIM_HandleTypeDef *htim);
void Get_Motor_Speed(int *leftSpeed, int *rightSpeed);
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define motor11_Pin GPIO_PIN_3
#define motor11_GPIO_Port GPIOA
#define motor12_Pin GPIO_PIN_4
#define motor12_GPIO_Port GPIOA
#define motor21_Pin GPIO_PIN_4
#define motor21_GPIO_Port GPIOC
#define motor22_Pin GPIO_PIN_5
#define motor22_GPIO_Port GPIOC
#define huidu11_Pin GPIO_PIN_15
#define huidu11_GPIO_Port GPIOB
#define huidu17_Pin GPIO_PIN_8
#define huidu17_GPIO_Port GPIOD
#define huidu21_Pin GPIO_PIN_9
#define huidu21_GPIO_Port GPIOD
#define huidu27_Pin GPIO_PIN_10
#define huidu27_GPIO_Port GPIOD
#define huidu22_Pin GPIO_PIN_10
#define huidu22_GPIO_Port GPIOC
#define huidu23_Pin GPIO_PIN_11
#define huidu23_GPIO_Port GPIOC
#define huidu24_Pin GPIO_PIN_12
#define huidu24_GPIO_Port GPIOC
#define huidu12_Pin GPIO_PIN_1
#define huidu12_GPIO_Port GPIOD
#define huidu14_Pin GPIO_PIN_3
#define huidu14_GPIO_Port GPIOD
#define huidu15_Pin GPIO_PIN_4
#define huidu15_GPIO_Port GPIOD
#define huidu16_Pin GPIO_PIN_5
#define huidu16_GPIO_Port GPIOD
#define huidu25_Pin GPIO_PIN_7
#define huidu25_GPIO_Port GPIOD
#define huidu26_Pin GPIO_PIN_3
#define huidu26_GPIO_Port GPIOB
#define huidu13_Pin GPIO_PIN_5
#define huidu13_GPIO_Port GPIOB
#define kaishi1_Pin GPIO_PIN_7
#define kaishi1_GPIO_Port GPIOB
#define HUIDU26_Pin GPIO_PIN_8
#define HUIDU26_GPIO_Port GPIOB
#define HUIDU23_Pin GPIO_PIN_9
#define HUIDU23_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
