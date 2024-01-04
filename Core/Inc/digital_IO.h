/*
 * digital_IO.h
 *
 *  Created on: Dec 31, 2023
 *      Author: ted
 */

#ifndef INC_DIGITAL_IO_H_
#define INC_DIGITAL_IO_H_

#include <stdbool.h>
#include "stm32f1xx_hal.h"

typedef enum {
	INPUT,
	INPUT_PWM,
	// ToDo: add hall and encoder input functionality
	OUTPUT,
	OUTPUT_PWM,						// only available for DIO 0,1,4,5
} dIO_type;

typedef struct {
	dIO_type		config;				// configure I/O and PWM
	bool			pullUp;				// pull-up inactive (0) or active (1)
	/* relevant for input */
	uint16_t		in_pin;
	GPIO_TypeDef	*in_gpiox;
	bool			in_value;			// (If config INPUT) current input value
	//float			in_freq;			// (If config INPUT_PWM) frequecy of input PWM
	//uint16_t		in_duty;			// (If config INPUT_PWM) duty cycle of input PWM
	/* relevant for output */
	uint16_t		out_pin;
	GPIO_TypeDef	*out_gpiox;
	bool			out_value;			// (If config OUTPUT) current output value
	bool			out_error;			// error bit if intended output state differs to input state
	// ToDo: add pwm output variables
} digitalIO;

extern	digitalIO	dIO_array[8];

void DIO_Init(void);
void DIO_Config(uint8_t index, dIO_type type);
void DIO_OutValue(uint8_t index, bool value);
void DIO_OutWrite(void);
void DIO_InRead(void);

#endif /* INC_DIGITAL_IO_H_ */
