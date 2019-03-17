/*
 * MotorController.cpp
 *
 *  Created on: 10 Mar 2019
 *      Author: omvir
 */

#include "MotorController.h"


MotorController::MotorController(int looptime) {
	// TODO Auto-generated constructor stub
	node = ModbusMaster(2); // Create modbus object that connects to slave id 2
	node.begin(9600); // set transmission rate - other parameters are set inside the object and can't be changed here
	ModbusRegister ControlWord(&node, 0);
	ModbusRegister StatusWord(&node, 3);
	freqcalc = PIDcalc(looptime,1000,-1000,60,14,0.43);

	ControlWord = 0x0406; // prepare for starting
	while((StatusWord & 0x01) != 1);

	ControlWord = 0x047F;// prepare to operate
	while((StatusWord & 0x02) != 0x02);

}
//return the frequency of the fan
int MotorController::getSpeed()
{
	ModbusRegister OutputFrequency(&node, 102);
	return (int)OutputFrequency;
}

//sets the speed for fan
int MotorController::setSpeed(int newSpeed)
{
	if(newSpeed < 0)
	{
		newSpeed = 0;
	}
	if(newSpeed > 20000)
	{
		newSpeed = 20000;
	}
	uint16_t freq = newSpeed;
	ModbusRegister Frequency(&node, 1);
	ModbusRegister Power(&node, 103);
	Frequency = freq;
	freq = Power;
	return freq;
}

//set the frequence of the fan
uint16_t MotorController::setFreq(int currentPressure, int desiredPressure)
{
	ModbusRegister Frequency(&node, 1);
	uint16_t freq;
	if(currentPressure == desiredPressure)
	{
		freq = getSpeed();
	} else {
		freq = getSpeed() + freqcalc.calculate(desiredPressure, currentPressure);
	}

	if(freq < 0)
	{
		freq = 0;
	}
	if(freq > 20000)
	{
		freq = 20000;
	}
	Frequency = freq;
	return freq;
}
MotorController::~MotorController() {
	// TODO Auto-generated destructor stub
}
