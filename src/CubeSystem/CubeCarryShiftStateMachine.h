/*
 * cubecarryshiftstatemachine.h
 *
 *  Created on: Jan 26, 2018
 *      Author: 1901319
 */


#ifndef SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_
#define SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_
#include "RobotCommands.h"
#include "IO.h"
#include "CubeManagerIO.h"
#include "cntl.h"


class CubeCarryShiftStateMachine {
public:
	cntl *testbutton;
	CubeManagerIO *CubeCarryShiftStateMachine(RobotCommands *Command, IO *RioIO);
	CubeCarryShiftStateMachine();
	virtual ~CubeCarryShiftStateMachine ();
private:
	int _cubecarryshiftstate;
	enum CUBECARRYSTAE{
		kLowShot,
		kScaleShot,
		kLowShotToScaleShot,
	};

};


#endif /* SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_ */
