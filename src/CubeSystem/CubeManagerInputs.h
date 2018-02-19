/*
 * CubeManagerInputs.h
 *
 *
 *  Created on: Feb 2, 2018
 *      Author: wentzdr
 *
 *  Abstraction class to store and regularly update all inputs used by the cube system
 *  Isolates the cube system state machines from the actual robot IO
 */

#ifndef SRC_CUBESYSTEM_CUBEMANAGERINPUTS_H_
#define SRC_CUBESYSTEM_CUBEMANAGERINPUTS_H_

#include "IO.h"

class CubeManagerInputs {
public:
	CubeManagerInputs();
	virtual ~CubeManagerInputs();

	enum class CubeSensor : bool {
		NO_CUBE_PRESENT = false,
		CUBE_PRESENT = true
	};

	CubeSensor getIntakeCubeSensor();
	CubeSensor getShooterCubeSensor();
	double getShooterAngleActualValue();
	bool armHomeSensor;

	//Function to poll all sensors in the cube system and update the stored values in this class
	void updateInputs(IO *Inputs);

private:
	//Variables to store the current value of each input sensor in the cube system
	CubeSensor intakeCubeSensor;
	CubeSensor shooterCubeSensor;
	double shooterangleactualvalue;
};

#endif /* SRC_CUBESYSTEM_CUBEMANAGERINPUTS_H_ */
