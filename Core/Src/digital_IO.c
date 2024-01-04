/*
 * digital_IO.c
 *
 *  Created on: Dec 31, 2023
 *      Author: ted
 */

#include "digital_IO.h"
#include "main.h"

digitalIO	dIO_array[8];

void DIO_Init(void) {
	for(int i=0; i<8; i++) {
		dIO_array[i].config = INPUT;
		dIO_array[i].in_value = 0;
		dIO_array[i].out_error = 0;
		dIO_array[i].out_value = 0;
		dIO_array[i].pullUp = 0;
	}

	dIO_array[0].in_gpiox = DIN_0_GPIO_Port;
	dIO_array[0].in_pin = DIN_0_Pin;
	dIO_array[0].out_gpiox = DOUT_0_GPIO_Port;
	dIO_array[0].out_pin = DOUT_0_Pin;

	dIO_array[1].in_gpiox = DIN_1_GPIO_Port;
	dIO_array[1].in_pin = DIN_1_Pin;
	dIO_array[1].out_gpiox = DOUT_1_GPIO_Port;
	dIO_array[1].out_pin = DOUT_1_Pin;

	dIO_array[2].in_gpiox = DIN_2_GPIO_Port;
	dIO_array[2].in_pin = DIN_2_Pin;
	dIO_array[2].out_gpiox = DOUT_2_GPIO_Port;
	dIO_array[2].out_pin = DOUT_2_Pin;

	dIO_array[3].in_gpiox = DIN_3_GPIO_Port;
	dIO_array[3].in_pin = DIN_3_Pin;
	dIO_array[3].out_gpiox = DOUT_3_GPIO_Port;
	dIO_array[3].out_pin = DOUT_3_Pin;

	dIO_array[4].in_gpiox = DIN_4_GPIO_Port;
	dIO_array[4].in_pin = DIN_4_Pin;
	dIO_array[4].out_gpiox = DOUT_4_GPIO_Port;
	dIO_array[4].out_pin = DOUT_4_Pin;

	dIO_array[5].in_gpiox = DIN_5_GPIO_Port;
	dIO_array[5].in_pin = DIN_5_Pin;
	dIO_array[5].out_gpiox = DOUT_5_GPIO_Port;
	dIO_array[5].out_pin = DOUT_5_Pin;

	dIO_array[6].in_gpiox = DIN_6_GPIO_Port;
	dIO_array[6].in_pin = DIN_6_Pin;
	dIO_array[6].out_gpiox = DOUT_6_GPIO_Port;
	dIO_array[6].out_pin = DOUT_6_Pin;

	dIO_array[7].in_gpiox = DIN_7_GPIO_Port;
	dIO_array[7].in_pin = DIN_7_Pin;
	dIO_array[7].out_gpiox = DOUT_7_GPIO_Port;
	dIO_array[7].out_pin = DOUT_7_Pin;

	/*
	 * ToDo: initialize as GPIO and attach to timer afterwards?
	 * configure PWM channels as GPIO:
	 */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DOUT_0_Pin|DOUT_1_Pin|DOUT_4_Pin|DOUT_5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	DIO_OutWrite();
}

void DIO_OutValue(uint8_t index, bool value) {
	dIO_array[index].out_value = value;
}

void DIO_Config(uint8_t index, dIO_type type) {
	dIO_array[index].config = type;
}

void DIO_OutWrite(void) {
	for(int i=0; i<8; i++) {
		switch(dIO_array[i].config) {
		case OUTPUT:
			HAL_GPIO_WritePin(dIO_array[i].out_gpiox, dIO_array[i].out_pin, !(dIO_array[i].out_value));		// !out_value since output is inverted
			break;
		case OUTPUT_PWM:
			// HAL Timer PWM anpassen
			break;
		default:
			HAL_GPIO_WritePin(dIO_array[i].out_gpiox, dIO_array[i].out_pin, GPIO_PIN_SET); // set output low if configured as input
		}
	}
}

void DIO_InRead(void) {
	for(int i=0; i<8; i++) {
		dIO_array[i].in_value = HAL_GPIO_ReadPin(dIO_array[i].in_gpiox, dIO_array[i].in_pin);
	}
}
