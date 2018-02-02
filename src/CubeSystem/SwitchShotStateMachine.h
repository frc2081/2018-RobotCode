/*
 * SwitchShotStateMachine.h
 *
 *  Created on: Jan 31, 2018
 *      Author: 2100433
 */

#ifndef SRC_CUBESYSTEM_SWITCHSHOTSTATEMACHINE_H_
#define SRC_CUBESYSTEM_SWITCHSHOTSTATEMACHINE_H_

#include "RobotCommands.h"
#include "IO.h"
#include "CubeManagerIO.h"

class SwitchShotStateMachine {
public:
	CubeManagerIO *SwitchShotStatePeriodic(RobotCommands *Command, IO *RioIO);
	SwitchShotStateMachine();
	virtual ~SwitchShotStateMachine();
private:
	enum Lowshot{
		LOWSHOT_PRESHOT,
		LOWSHOT_SHOOT,
		LOWSHOT_POSTSHOT,
	};
	Lowshot switchshotcommand;
	int switchshottimer;
};


#endif /* SRC_CUBESYSTEM_SWITCHSHOTSTATEMACHINE_H_ */
