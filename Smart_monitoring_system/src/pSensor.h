/*
 * pSensor.h
 *
 *  Created on: 8 Mar 2019
 *      Author: Valtsu
 */

#ifndef PSENSOR_H_
#define PSENSOR_H_

#include "I2C.h"
#include "board.h"


//pSensor inherits I2C
class pSensor : public I2C {
public:
	pSensor(I2C_config &conf, int dA, int cmd);
	virtual ~pSensor();
	int getReading();


private:
	uint8_t devAddr;
	uint8_t command;
};

#endif /* PSENSOR_H_ */
