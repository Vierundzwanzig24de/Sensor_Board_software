/*
 * usb.h
 *
 *  Created on: Jan 4, 2024
 *      Author: ted
 */

#ifndef INC_USB_H_
#define INC_USB_H_

typedef enum {
	STATUS,
	DIAGNOSTICS,
	DIGITALIO,
	ANALOGIN,
	POWEROUT,
} usb_frame;

void USB_sendFrame(usb_frame);

#endif /* INC_USB_H_ */
