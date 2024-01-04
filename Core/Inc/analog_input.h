/*
 * analog_input.h
 *
 *  Created on: 24.12.2023
 *      Author: ted
 */

#ifndef INC_ANALOG_INPUT_H_
#define INC_ANALOG_INPUT_H_

#include <stdbool.h>
#include "stm32f1xx_hal.h"

typedef enum {
	VOLT,
	AMPERE,
	CELSIUS,
	BAR,
	MBAR,
	DEGREES,
	MILLIMETER,
	NEWTON,
	HERTZ,
	RPM,
	PERCENT,
} aIn_unit;

typedef enum {
	ACTIVE,
	PT1000,
	NTC,
	DIGITAL,
} aIn_sensor;

typedef struct {
	uint16_t 	adc_value;			// value from adc (12-bit)
	uint16_t 	adc_max;			// adc upper limit (maximum voltage of sensor converted to adc bits)
	uint16_t 	adc_min;			// adc lower limit (minimum voltage of sensor converted to adc bits)
	float		adc_conv;			// conversion factor from adc_value to unit_value in range adc_max adc_min
	float		sensor_offset;		// sensor_value of sensor at adc_min
	float		sensor_value;		// sensor value converted to real units
	aIn_unit	sensor_unit;		// sensor measurement unit
	aIn_sensor	sensor_type;		// sensor type (active, pt1000, ntc, digital)
	bool		pullR_type;			// pull-down (0) or pull-up (1)
	float		pullR_value;		// value of pull resistor (used for passive sensor calculations)
	bool		err_nc;				// error bit sensor not connected (if adc_value close to supply or ground depending on pullR_type)
	bool		err_ov;				// error bit if adc_value > adc_max
	bool		err_uv;				// error bit if adc_value < adc_max
} analogIn;

extern analogIn	aIn_array[8];

void AIN_Init(I2C_HandleTypeDef *hi2c);
void AIN_Config(uint8_t index, analogIn config);
void AIN_Read(void);

#endif /* INC_ANALOG_INPUT_H_ */
