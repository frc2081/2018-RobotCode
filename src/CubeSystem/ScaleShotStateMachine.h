/*
 * ScaleShotStateMachine.h
 *
 *  Created on: Feb 1, 2018
 *      Author: 1901319
 */

#ifndef SRC_CUBESYSTEM_SCALESHOTSTATEMACHINE_H_
#define SRC_CUBESYSTEM_SCALESHOTSTATEMACHINE_H_
#include "RobotCommands.h"
#include "IO.h"
#include "CubeManagerInputs.h"
#include "CubeManagerOUtputs.h"
#include "ControllerInput/cntl.h"

class ScaleShotStateMachine {
public:
	CubeManagerOutputs *ScaleShotStatePeriodic(RobotCommands *Command, CubeManagerInputs *Inputs);
	ScaleShotStateMachine();
	virtual ~ScaleShotStateMachine();
	double placeholderforactualshooterangle = 75;
	// timer that waits until the arm is angled correctly and the wheels are spinning
	int scaleshotwaitingtimer = 600;
	// timer that waits until the cube is shoot before leaving the kshootingcube state
	int scaleshotresettimer = 50;
	// 75 is the angle we want the shooter arm to be angled at
	int scaleshotarmangle = 75;
	// 1 is the motors 100% power
	int motermaxpower = 1;
private:
	enum SCALESHOTSTATE{
		kwaitingtoshoot,
		kanglingshooter,
		kshootingcube,
		kreseting
	};
	SCALESHOTSTATE _scaleshotstate;
};

#endif /* SRC_CUBESYSTEM_SCALESHOTSTATEMACHINE_H_ */
