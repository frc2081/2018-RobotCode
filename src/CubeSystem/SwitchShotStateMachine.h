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
#include "CubeManagerOutputs.h"
#include "CubeManagerInputs.h"

class SwitchShotStateMachine {
public:
	CubeManagerOutputs *SwitchShotStatePeriodic(RobotCommands *Commands, CubeManagerInputs *Inputs);
	SwitchShotStateMachine();
	virtual ~SwitchShotStateMachine();
private:
	enum Lowshot{
		LOWSHOT_BUTTONCHECK,
		LOWSHOT_PRESHOT,
		LOWSHOT_SHOOT,
		LOWSHOT_POSTSHOT,
	};
	Lowshot switchshotcommand;
	int switchshottimer;

	//****Calibrations****
	const int switchshottimerreset = 300;
	const double lowshooterangle = 500;
	const double intakeshooterangle = 0;
	const double lowshooterpower = 0.3;
	const double noshooterpower = 0;
	const double shooteranglemargin = 2;
};


#endif /* SRC_CUBESYSTEM_SWITCHSHOTSTATEMACHINE_H_ */
