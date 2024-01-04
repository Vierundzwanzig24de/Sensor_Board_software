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
#include "stm32f1xx_hal.h"

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
#define STATUS_LED_Pin GPIO_PIN_13
#define STATUS_LED_GPIO_Port GPIOC
#define CAN_STBY_Pin GPIO_PIN_14
#define CAN_STBY_GPIO_Port GPIOC
#define LIN_EN_Pin GPIO_PIN_15
#define LIN_EN_GPIO_Port GPIOC
#define IS_1A_Pin GPIO_PIN_0
#define IS_1A_GPIO_Port GPIOC
#define IS_HB0_Pin GPIO_PIN_1
#define IS_HB0_GPIO_Port GPIOC
#define IS_HB1_Pin GPIO_PIN_2
#define IS_HB1_GPIO_Port GPIOC
#define VS_5VA_Pin GPIO_PIN_3
#define VS_5VA_GPIO_Port GPIOC
#define DOUT_0_Pin GPIO_PIN_0
#define DOUT_0_GPIO_Port GPIOA
#define DOUT_1_Pin GPIO_PIN_1
#define DOUT_1_GPIO_Port GPIOA
#define DOUT_4_Pin GPIO_PIN_2
#define DOUT_4_GPIO_Port GPIOA
#define DOUT_5_Pin GPIO_PIN_3
#define DOUT_5_GPIO_Port GPIOA
#define VS_Vdrive_Pin GPIO_PIN_4
#define VS_Vdrive_GPIO_Port GPIOA
#define IN_SRCLK_Pin GPIO_PIN_5
#define IN_SRCLK_GPIO_Port GPIOA
#define IN_RCLK_Pin GPIO_PIN_6
#define IN_RCLK_GPIO_Port GPIOA
#define IN_SRD_Pin GPIO_PIN_7
#define IN_SRD_GPIO_Port GPIOA
#define DOUT_2_Pin GPIO_PIN_4
#define DOUT_2_GPIO_Port GPIOC
#define DOUT_3_Pin GPIO_PIN_5
#define DOUT_3_GPIO_Port GPIOC
#define DOUT_6_Pin GPIO_PIN_0
#define DOUT_6_GPIO_Port GPIOB
#define DOUT_7_Pin GPIO_PIN_1
#define DOUT_7_GPIO_Port GPIOB
#define EEPROM_WP_Pin GPIO_PIN_2
#define EEPROM_WP_GPIO_Port GPIOB
#define EEPROM_SCL_Pin GPIO_PIN_10
#define EEPROM_SCL_GPIO_Port GPIOB
#define EEPROM_SDA_Pin GPIO_PIN_11
#define EEPROM_SDA_GPIO_Port GPIOB
#define POUT_1A_0_Pin GPIO_PIN_12
#define POUT_1A_0_GPIO_Port GPIOB
#define POUT_1A_1_Pin GPIO_PIN_13
#define POUT_1A_1_GPIO_Port GPIOB
#define POUT_1A_2_Pin GPIO_PIN_14
#define POUT_1A_2_GPIO_Port GPIOB
#define POUT_1A_3_Pin GPIO_PIN_15
#define POUT_1A_3_GPIO_Port GPIOB
#define POUT_Half0_Pin GPIO_PIN_6
#define POUT_Half0_GPIO_Port GPIOC
#define POUT_Half1_Pin GPIO_PIN_7
#define POUT_Half1_GPIO_Port GPIOC
#define POUT_HalfINH_Pin GPIO_PIN_8
#define POUT_HalfINH_GPIO_Port GPIOC
#define POUT_1A_DSEL1_Pin GPIO_PIN_9
#define POUT_1A_DSEL1_GPIO_Port GPIOC
#define POUT_1A_DSEL0_Pin GPIO_PIN_8
#define POUT_1A_DSEL0_GPIO_Port GPIOA
#define LIN_TX_Pin GPIO_PIN_9
#define LIN_TX_GPIO_Port GPIOA
#define LIN_RX_Pin GPIO_PIN_10
#define LIN_RX_GPIO_Port GPIOA
#define DIN_7_Pin GPIO_PIN_15
#define DIN_7_GPIO_Port GPIOA
#define DIN_4_Pin GPIO_PIN_10
#define DIN_4_GPIO_Port GPIOC
#define DIN_5_Pin GPIO_PIN_11
#define DIN_5_GPIO_Port GPIOC
#define DIN_6_Pin GPIO_PIN_12
#define DIN_6_GPIO_Port GPIOC
#define DIN_3_Pin GPIO_PIN_2
#define DIN_3_GPIO_Port GPIOD
#define DIN_0_Pin GPIO_PIN_3
#define DIN_0_GPIO_Port GPIOB
#define DIN_1_Pin GPIO_PIN_4
#define DIN_1_GPIO_Port GPIOB
#define DIN_2_Pin GPIO_PIN_5
#define DIN_2_GPIO_Port GPIOB
#define ADC_SCL_Pin GPIO_PIN_6
#define ADC_SCL_GPIO_Port GPIOB
#define ADC_SDA_Pin GPIO_PIN_7
#define ADC_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
