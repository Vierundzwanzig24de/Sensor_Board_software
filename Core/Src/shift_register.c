/*
 * shift_register.c
 *
 *  Created on: Dec 22, 2023
 *      Author: ted
 */

#include "shift_register.h"
#include "analog_input.h"
#include "digital_IO.h"
#include "main.h"

#define SR_DAISY_CHAIN		2		// number of shift registers in series
#define SR_MIN_PULSE_LENGTH	1		// [µs] at least 100ns according to SN74HC595 datasheet

static SPI_HandleTypeDef *sr_hspi;
static GPIO_TypeDef *sr_GPIO;
static uint16_t sr_GPIO_Pin;

// ToDo: take initial values from EEPROM
void SR_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	sr_hspi = hspi;
	sr_GPIO = GPIOx;
	sr_GPIO_Pin = GPIO_Pin;
	HAL_GPIO_WritePin(sr_GPIO, sr_GPIO_Pin, GPIO_PIN_RESET);
	SR_Update();
}

void SR_Update(void) {
	/* SR order: dIn, aIn so aIn byte has to be sent first
	 * bit order: LSB first -> MSB=7 .. LSB=0
	 */
	uint8_t data_aIn = 0;
	uint8_t data_dIn = 0;
	// config analogIn:
	data_aIn |= 0b00000001 & aIn_array[0].pullR_type;
	data_aIn |= 0b00000010 & (aIn_array[1].pullR_type << 1);
	data_aIn |= 0b00000100 & (aIn_array[2].pullR_type << 2);
	data_aIn |= 0b00001000 & (aIn_array[3].pullR_type << 3);
	data_aIn |= 0b00010000 & (aIn_array[4].pullR_type << 4);
	data_aIn |= 0b00100000 & (aIn_array[5].pullR_type << 5);
	data_aIn |= 0b01000000 & (aIn_array[6].pullR_type << 6);
	data_aIn |= 0b10000000 & (aIn_array[7].pullR_type << 7);
	// config digitalIn:
	data_dIn |= 0b00000001 & dIO_array[0].pullUp;
	data_dIn |= 0b00000010 & (dIO_array[1].pullUp << 1);
	data_dIn |= 0b00000100 & (dIO_array[2].pullUp << 2);
	data_dIn |= 0b00001000 & (dIO_array[3].pullUp << 3);
	data_dIn |= 0b00010000 & (dIO_array[4].pullUp << 4);
	data_dIn |= 0b00100000 & (dIO_array[5].pullUp << 5);
	data_dIn |= 0b01000000 & (dIO_array[6].pullUp << 6);
	data_dIn |= 0b10000000 & (dIO_array[7].pullUp << 7);

	uint8_t data[2]={data_aIn,data_dIn};
	SR_WriteData(data);
	SR_OutputData();
}

void SR_WriteData(uint8_t data[SR_DAISY_CHAIN]){
	if(HAL_SPI_Transmit(sr_hspi, data, SR_DAISY_CHAIN, HAL_MAX_DELAY) != HAL_OK){
		Error_Handler();
	}
}

// ToDo: add µs delay based on mainloop counter
void SR_OutputData(void){
	HAL_GPIO_WritePin(sr_GPIO, sr_GPIO_Pin, GPIO_PIN_SET);
	//HAL_Delay(SR_MIN_PULSE_LENGTH); funktioniert vielleicht ohne?
	HAL_GPIO_WritePin(sr_GPIO, sr_GPIO_Pin, GPIO_PIN_RESET);
}
