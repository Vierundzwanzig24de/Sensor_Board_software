/*
 * max11614.h
 *
 *  Created on: 23.12.2023
 *      Author: ted
 */

#ifndef INC_MAX11614_H_
#define INC_MAX11614_H_

#include "stm32f1xx_hal.h"

void MAX11614_Init(I2C_HandleTypeDef *hi2c, uint8_t refVoltage);
uint16_t MAX11614_ReadSingleCh(uint8_t channel);
void MAX11614_ReadAllCh(uint16_t *data);


#endif /* INC_MAX11614_H_ */
