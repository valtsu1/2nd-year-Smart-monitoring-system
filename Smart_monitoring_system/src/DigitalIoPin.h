/*
 * DigitalIoPin.h
 *
 *  Created on: Jan 23, 2019
 *      Author: valtsu
 */

#ifndef DIGITALIOPIN_H_
#define DIGITALIOPIN_H_

class DigitalIoPin {
public:
	DigitalIoPin(int port, int pin, bool input = true, bool pullup = true, bool invert = false);
	virtual ~DigitalIoPin();
	bool read();
	void write(bool value);
private:
	int pin;
	int port;
	bool invert;
	// add these as needed
};

#endif /* DIGITALIOPIN_H_ */
