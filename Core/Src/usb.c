/*
 * usb.c
 *
 *  Created on: Jan 4, 2024
 *      Author: ted
 */

#include "usb.h"
#include "usbd_cdc_if.h"
#include "analog_input.h"
#include "digital_IO.h"
#include "main.h"

/*
 * USB Tx frame format:
 * 1 byte identifier
 */

void USB_sendFrame(usb_frame frame) {
	uint8_t data[3] = {0}; // longest data for AnalogIn
	switch(frame) {
	case STATUS:
		// Status frame
		break;
	case DIAGNOSTICS:
		// Diagnostics (Errors, Voltages, Temperature)
		break;
	case DIGITALIO:
		/* Frame: [0]identifier, [1]dIn, [2]dOut */
		data[0] = DIGITALIO;
		data[1] |= 0b00000001 & (dIO_array[0].in_value << 0);
		data[1] |= 0b00000010 & (dIO_array[1].in_value << 1);
		data[1] |= 0b00000100 & (dIO_array[2].in_value << 2);
		data[1] |= 0b00001000 & (dIO_array[3].in_value << 3);
		data[1] |= 0b00010000 & (dIO_array[4].in_value << 4);
		data[1] |= 0b00100000 & (dIO_array[5].in_value << 5);
		data[1] |= 0b01000000 & (dIO_array[6].in_value << 6);
		data[1] |= 0b10000000 & (dIO_array[7].in_value << 7);
		data[2] |= 0b00000001 & (dIO_array[0].out_value << 0);
		data[2] |= 0b00000010 & (dIO_array[1].out_value << 1);
		data[2] |= 0b00000100 & (dIO_array[2].out_value << 2);
		data[2] |= 0b00001000 & (dIO_array[3].out_value << 3);
		data[2] |= 0b00010000 & (dIO_array[4].out_value << 4);
		data[2] |= 0b00100000 & (dIO_array[5].out_value << 5);
		data[2] |= 0b01000000 & (dIO_array[6].out_value << 6);
		data[2] |= 0b10000000 & (dIO_array[7].out_value << 7);
		CDC_Transmit_FS(data,3);
		break;
	case ANALOGIN :
		/* Frame: [0]identifier, [1]MSB_aIn0, [2]LSB_aIn0, [3]MSB_aIn1, ... */
		data[0] = ANALOGIN;
		data[1] = ((uint16_t)aIn_array[0].adc_value >> 8) & 0xFF;
		data[2] = ((uint16_t)aIn_array[0].adc_value >> 0) & 0xFF;
		CDC_Transmit_FS(data,3);
		break;
	case POWEROUT:
		// Power outputs
		break;
	default:
		break;
	}
}
