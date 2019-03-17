/*
 * pSensor.cpp
 *
 *  Created on: 8 Mar 2019
 *      Author: Valtsu
 */

#include "pSensor.h"

//constructor, inherits I2C
pSensor::pSensor(I2C_config &conf, int dA, int cmd) : I2C(conf) {
	devAddr = dA;
	command = cmd;
}

pSensor::~pSensor() {
	// TODO Auto-generated destructor stub
}

//returns preassure in pascals, communicates using I2C
//Sensor returns 3 bits, commbining two first bits makes preasure value
//after that we turn the value into Pascals using the values in SPD600 datasheet
int pSensor::getReading() {
	uint8_t arr[3];
	int16_t pressure;
	transaction(devAddr, &command, 1, arr, 3);
	pressure = arr[0];
	//shifting left
	pressure = pressure << 8;
	pressure |= arr[1];
	//conversion to pascal
	pressure /= 240;
	//altitude correction for 0 to 250 meters above the sealevel
	pressure *= 0.95;
	return pressure;
}

