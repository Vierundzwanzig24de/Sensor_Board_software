/*
 * shift_register.h
 *
 *  Created on: Dec 22, 2023
 *      Author: ted
 */

#ifndef INC_SHIFT_REGISTER_H_
#define INC_SHIFT_REGISTER_H_

#include "stm32f1xx_hal.h"

void SR_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SR_Update(void);
void SR_WriteData(uint8_t data[]);
void SR_OutputData(void);


#endif /* INC_SHIFT_REGISTER_H_ */
