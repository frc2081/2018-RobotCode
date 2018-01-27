/*
 * cubecarryshiftstatemachine.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: 1901319
 */

#include <CubeSystem/CubeCarryShiftStateMachine.h>
int count = 50;
CubeManagerIO  *CubeCarryShiftStateMachine::CubeCarryShiftState(RobotCommands *Command, IO *RioIO)
{
	switch(_cubecarryshiftstate)
	{
		case kLowShot:
			RioIO->solenoidpoker->Set(true);
			if (testbutton->bX->State())
			{
				_cubecarryshiftstate = kLowShotToScaleShot;
				break;
			}
		break;
		case kLowShotToScaleShot:
			RioIO->solenoidpoker->Set(false);
			RioIO->intakelmot->Set(0.5);
			RioIO->intakermot->Set(0.5);
			RioIO->shooterlmot->Set(0.5);
			RioIO->shooterrmot->Set(0.5);
			count = count - 1;
			if (count == 0)
			{
				_cubecarryshiftstate = kScaleShot;
				break;
			}
			/* no break */
		case kScaleShot:
			RioIO->solenoidpoker->Set(false);
			if (testbutton->bX->State())
			{
				_cubecarryshiftstate = kScaleShot;
				break;
			}
	}
	return ;
}

CubeCarryShiftStateMachine::CubeCarryShiftStateMachine() {
	// TODO Auto-generated constructor stub
	_cubecarryshiftstate = kLowShot;
	testbutton = new cntl(0, 0.3);
}

CubeCarryShiftStateMachine::~CubeCarryShiftStateMachine() {
	// TODO Auto-generated destructor stub
}

