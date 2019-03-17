/*
 * PIDcalc.cpp
 *
 *  Created on: 11 Mar 2019
 *      Author: omvir
 */

#include "PIDcalc.h"
PIDcalc::PIDcalc()
{

}
PIDcalc::PIDcalc(float dt, float max, float min, float Kp, float Kd, float Ki) :

		_dt(dt), _max(max), _min(min), _Kp(Kp), _Kd(Kd), _Ki(Ki), _pre_error(0), _integral(
				0) {
	// Kp -  proportional gain
	// Ki -  Integral gain
	// Kd -  derivative gain
	// dt -  loop interval time
	// max - maximum value of manipulated variable
	// min - minimum value of manipulated variable
}

float PIDcalc::calculate(float desiredValue, float currentValue) {
	// Calculate error
	float error = desiredValue - currentValue;

	// Proportional term
	float Pout = _Kp * error;

	// Integral term
	_integral += error * _dt;
	float Iout = _Ki * _integral;

	// Derivative term
	float derivative = (error - _pre_error) / _dt;
	float Dout = _Kd * derivative;

	// Calculate total output
	float output = Pout + Iout + Dout;

	// Restrict to max/min
	if (output > _max)
		output = _max;
	else if (output < _min)
		output = _min;

	// Save error to previous error
	_pre_error = error;

	return output;
}

PIDcalc::~PIDcalc() {
	// TODO Auto-generated destructor stub
}

