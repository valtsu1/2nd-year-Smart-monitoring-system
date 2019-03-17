/*
 * MotorController.h
 *
 *  Created on: 10 Mar 2019
 *      Author: omvir
 */

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#include "ModbusMaster.h"
#include "ModbusRegister.h"
#include "PIDcalc.h"

class MotorController {
public:
	MotorController(int looptime);
	int getSpeed();
	uint16_t setFreq(int currentPressure, int DesiredPressure);
	int setSpeed(int newSpeed);
	virtual ~MotorController();
private:
	ModbusMaster node;
	PIDcalc freqcalc;

};

#endif /* MOTORCONTROLLER_H_ */
