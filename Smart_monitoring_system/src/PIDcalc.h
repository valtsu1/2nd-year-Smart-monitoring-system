/*
 * PIDcalc.h
 *
 *  Created on: 11 Mar 2019
 *      Author: omvir
 */

#ifndef PIDCALC_H_
#define PIDCALC_H_

class PIDcalc {
public:
	PIDcalc();
	PIDcalc(float dt, float max, float min, float Kp, float Kd, float Ki);
	float calculate( float setpoint, float pv );
	virtual ~PIDcalc();
private:
       float _dt;
       float _max;
       float _min;
       float _Kp;
       float _Kd;
       float _Ki;
       float _pre_error;
       float _integral;
};

#endif /* PIDCALC_H_ */
