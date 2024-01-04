/*
 * max11614.c
 *
 *  Created on: 23.12.2023
 *      Author: ted
 */


#include "max11614.h"
#include "main.h"

// I2C Device address:
#define MAX11614_I2C_ADD		(0b0110011 << 1)	// left shift because HAL_I2C_Transmit() said so

// Bipolar / Unipolar
/*
#define MAX11614_IN_UNI			0x00	// unipolar inputs
#define MAX11614_IN_BIP			0x01	// bipolar inputs
*/

// Clock selection:
/*
#define MAX11614_CLK_INT		0x00	// internal clock (default)
#define MAX11614_CLK_EXT		0x01	// external clock
*/

// Scan selection (datasheet table 5):
/*
#define MAX11614_SCAN_UNTIL		0x00	// scan from AIN0 to input selected by CS2-CS0 (CS3 internally set low)
#define MAX11614_SCAN_SINGLE_HS	0x01	// scan input selected by CS2-CS0 eight times (if internal clock mode)
#define MAX11614_SCAN_UPPER_Q	0x02	// scan upwards from AIN6 until input selected by CS2-CS0 (AIN6 and AIN7 max.)
#define MAX11614_SCAN_SINGLE	0x03	// scan input selected by CS2-CS0
*/

// Reference voltage selection (datasheet table 6):
#define MAX11614_REF_VDD		0x00	// use supply voltage as reference
#define MAX11614_REF_EXT		0x02	// use external voltage at pin REF
#define MAX11614_REF_INT_NC		0x04	// use internal reference, pin REF is not connected
#define MAX11614_REF_INT_OUT	0x06	// use internal reference, output internal reference at pin REF
#define MAX11614_REF_INT_OFF	0x00	// initialize with internal reference off
#define MAX11614_REF_INT_ON		0x01	// if internal reference is used, wait 10ms before turning on



static I2C_HandleTypeDef *max11614_hi2c;


// ToDo?: add input and clock configuration
void MAX11614_Init(I2C_HandleTypeDef *hi2c, uint8_t refVoltage){
	max11614_hi2c = hi2c;
	uint8_t sendByte = 0;
	/*
	 * Setup byte:
	 * 0 	- don't care
	 * 1 	- reset (sets config register to default values)
	 * 2 	- select bipolar/unipolar inputs
	 * 3 	- select clock source
	 * 4-6	- select reference voltage
	 * 7	- register bit (1=setup, 0=config)
	 */
	sendByte = (refVoltage<<4) | 0b0010;	// internal clock, unipolar inputs, no reset
	sendByte |= 0x80;	// configure byte as setup byte
	if(HAL_I2C_Master_Transmit(max11614_hi2c, MAX11614_I2C_ADD, &sendByte, 1, HAL_MAX_DELAY) != HAL_OK){
		Error_Handler();
	}
	// If internal voltage reference selected, turn on after 10ms:
	if((refVoltage==MAX11614_REF_INT_NC)||(refVoltage==MAX11614_REF_INT_OUT)) {
		HAL_Delay(10000);	// 10ms delay until internal reference is awake
		sendByte |= (MAX11614_REF_INT_ON<<4);
		if(HAL_I2C_Master_Transmit(max11614_hi2c, MAX11614_I2C_ADD, &sendByte, 1, HAL_MAX_DELAY) != HAL_OK){
			Error_Handler();
		}
	}
	/*
	 * Configuration byte
	 * 0 	- single-ended / differential input
	 * 1-3 	- CS0-2 channel select bits
	 * 4	- CS3 internally set to 0
	 * 5,6	- scan select bits (default 00 - scan from AIN0 to AINx selected by CS0-2)
	 * 7	- register bit (1=setup, 0=config)
	 */
	sendByte = 0; // all default for initialization
	if(HAL_I2C_Master_Transmit(max11614_hi2c, MAX11614_I2C_ADD, &sendByte, 1, HAL_MAX_DELAY) != HAL_OK){
		Error_Handler();
	}
}

uint16_t MAX11614_ReadSingleCh(uint8_t channel){
	uint8_t configByte = 0b01100001;
	uint8_t buffer[2] = {0,0};
	uint16_t result = 0;

	channel &= 0x7;
	configByte |= (channel<<1);
	if(HAL_I2C_Master_Transmit(max11614_hi2c, MAX11614_I2C_ADD, &configByte, 1, 10) != HAL_OK){
		Error_Handler();
	}
	HAL_I2C_Master_Receive(max11614_hi2c, MAX11614_I2C_ADD, buffer, 2, 10);

	result = (((uint16_t)buffer[0] & 0x000f) << 8) + buffer[1];
	return result;
}

void MAX11614_ReadAllCh(uint16_t *data){
	uint8_t configByte = 0b00001111;
	uint8_t buffer[16] = {0};
	if(HAL_I2C_Master_Transmit(max11614_hi2c, MAX11614_I2C_ADD, &configByte, 1, 10) != HAL_OK){
		Error_Handler();
	}
	HAL_I2C_Master_Receive(max11614_hi2c, MAX11614_I2C_ADD, buffer, 16, 10);

	for (int i=0; i<8; i++) {
		data[i] = (((uint16_t)buffer[i*2] & 0x000f) << 8) + buffer[i*2+1];
	}
}
