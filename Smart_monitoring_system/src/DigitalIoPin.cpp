/*
 * DigitalIoPin.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: valtsu
 */

#include "DigitalIoPin.h"
#include "board.h"

DigitalIoPin::DigitalIoPin(int po, int pi, bool input, bool pullup, bool inv){
	port = po;
	pin = pi;
	invert = inv;
	if(input){
		if(invert && pullup){
			Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
		}
		else if (invert && !pullup){
			Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin,  (IOCON_DIGMODE_EN | IOCON_INV_EN));
		}
		else if (!invert && pullup){
			Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN));
		}
		else{
			Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_DIGMODE_EN));
		}
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);
	}
	else{
		Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, port, pin);
	}
}


DigitalIoPin::~DigitalIoPin() {
	// TODO Auto-generated destructor stub
}

bool DigitalIoPin::read(){
	bool rbool = false;
	if(	Chip_GPIO_GetPinState(LPC_GPIO, port, pin)){
		rbool = true;
		//ITM_write("pin pressed\n");
	}
	return rbool;
}

void DigitalIoPin::write(bool value){
	if(invert){
		value =!value;
	}
	Chip_GPIO_SetPinState(LPC_GPIO, port, pin, value);
}
