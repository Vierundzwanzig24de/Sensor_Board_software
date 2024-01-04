/*
 * analog_input.c
 *
 *  Created on: 24.12.2023
 *      Author: ted
 */

#include "analog_input.h"
#include "max11614.h"
#include "main.h"

analogIn	aIn_array[8];

void AIN_Init(I2C_HandleTypeDef *hi2c) {
	MAX11614_Init(hi2c, 0x02);
	for(int i=0; i<8; i++) {
		aIn_array[i].adc_value = 0;
		aIn_array[i].adc_max = 3686;
		aIn_array[i].adc_min = 410;
		aIn_array[i].adc_conv = 0.001221;
		aIn_array[i].sensor_offset = 0;
		aIn_array[i].sensor_value = 0;
		aIn_array[i].sensor_unit = VOLT;
		aIn_array[i].sensor_type = ACTIVE;
		if(i>5) {
			aIn_array[i].pullR_type = 1;
			aIn_array[i].pullR_value = 1000;
		}
		else {
			aIn_array[i].pullR_type = 0;
			aIn_array[i].pullR_value = 10000;
		}
		aIn_array[i].err_nc = 0;
		aIn_array[i].err_ov = 0;
		aIn_array[i].err_uv = 0;
	}
}

void AIN_Config(uint8_t index, analogIn config) {
	// ToDo: add rest of struct
	aIn_array[index].sensor_type = config.sensor_type;
}

void AIN_Read(void) {
	uint16_t buffer[8] = {0};
	MAX11614_ReadAllCh(buffer);
	for(int i=0; i<8; i++) {
		aIn_array[i].adc_value = buffer[i];
		aIn_array[i].sensor_value = aIn_array[i].adc_value * aIn_array[i].adc_conv;
		// ToDo: add complete conversion and error checking
	}
}
