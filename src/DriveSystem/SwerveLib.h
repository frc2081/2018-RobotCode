/* Copyright 2018 FRC Icarus 2081 */

#ifndef SWERVELIB_H_
#define SWERVELIB_H_

#include <cmath>

const double PI = 3.14159265;

class wheel {
public:
	// front right, front left, rear left, rear right
	double speedRF, speedLF, speedLB, speedRB;
	double angleRF, angleLF, angleLB, angleRB;
};

class SwerveLib {
private:
	// Wanted speeds for the wheels
	double _targetWhlSpeed_RF = 0, _targetWhlSpeed_LF = 0, _targetWhlSpeed_LB = 0, _targetWhlSpeed_RB = 0, _MaxWhlSpeed = 0;
	// Wanted angles for the wheels
	double _targetWhlAng_RF = 0, _targetWhlAng_LF = 0, _targetWhlAng_LB = 0, _targetWhlAng_RB = 0;
	// Vectors for the wheels' motion, and dimensions of robot.
	// Width is wheelbase, length is trackwidth, radius is one corner to center
	double _A = 0, _B = 0, _C = 0, _D = 0;
	double _radius, _width, _length;
	// Last commanded angle for wheels
	double _currAngRF = 0, _currAngLF = 0, _currAngLB = 0, _currAngRB = 0;
	// Motion the center of the robot wants to take
	double _centerVecX = 0, _centerVecY = 0;
	/*
	 * Wheel 1
	 * 	X = B
	 * 	Y = C
	 * Wheel 2
	 *	X = B
	 *	Y = D
	 * Wheel 3
	 * 	X = A
	 * 	Y = D
	 * Wheel 4
	 * 	X = A
	 * 	Y = C
	 */
public:
    SwerveLib(double wheelbase, double trackwidth);

    virtual ~SwerveLib() = default;

    wheel *whl;

    void CalcWheelVect(double mag, double ang, double rotation);
};
#endif //SWERVELIB_H_
