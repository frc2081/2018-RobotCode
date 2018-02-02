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
#include "CubeManagerIO.h"
#include "ControllerInput/cntl.h"

class ScaleShotStateMachine {
public:
	CubeManagerIO *ScaleShotStatePeriodic(RobotCommands *Command, IO *RioIO);
	ScaleShotStateMachine();
	virtual ~ScaleShotStateMachine();
	double placeholderforactualshooterangle = 75;
	int scaleshotwaitingtimer = 600;
	int scaleshotresettimer = 50;
private:
	enum SCALESHOTSTATE{
		kwaitingtoshoot,
		kanglingshooter,
		kshootingcube,
	};
	SCALESHOTSTATE _scaleshotstate;
};

#endif /* SRC_CUBESYSTEM_SCALESHOTSTATEMACHINE_H_ */
