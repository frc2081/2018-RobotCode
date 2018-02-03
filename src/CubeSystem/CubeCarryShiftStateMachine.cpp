/*
 * cubecarryshiftstatemachine.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: 1901319
 * state machine that switches the location that the cube is being carried
 */

#include <CubeSystem/CubeCarryShiftStateMachine.h>

namespace CubeSystem {

	CubeManagerOutputs  *CubeCarryShiftStateMachine::CubeCarryShiftStatePeriodic(RobotCommands *Command, CubeManagerInputs *Inputs)
// this is the main loop for the cube carry shift state machine
	{
		CubeManagerOutputs *cubeio = new CubeManagerOutputs();
		switch(_cubecarryshiftstate)
		{
		// state for low carry \ switch shot and exchange shot
			case kLowShot:
				cubeio->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
				cubeio->intakepowercmd = 0;
				cubeio->shooterpowercmd = 0;
				cubeio->shooteranglecmd = Inputs->getShooterAngleActualValue();

				cubeio->isdone = true;

				if (Command->cmdshiftcube)
				{
					_cubecarryshiftstate = kLowShotToScaleShot;
				}
				break;
			// state for switching low carry to high carry
			case kLowShotToScaleShot:
				cubeio->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
				cubeio->intakepowercmd = cubecarryshiftintakepower;
				cubeio->shooterpowercmd = cubecarryshiftshooterpower;
				cubeio->shooteranglecmd = Inputs->getShooterAngleActualValue();

				cubeintaketimer = cubeintaketimer - 1;
				if (cubeintaketimer == 0)
				{
					_cubecarryshiftstate = kScaleShot;
					cubeintaketimer = cubeshiftduration;
				}
				break;
			// state for high carry \ scale shot
			case kScaleShot:
				cubeio->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
				cubeio->intakepowercmd = 0;
				cubeio->shooterpowercmd = 0;
				cubeio->shooteranglecmd = Inputs->getShooterAngleActualValue();

				cubeio->isdone = true;

				if (Command->cmdshiftcube)
				{
					_cubecarryshiftstate = kLowShot;
				}
				break;
		}
		return cubeio;
	}

	CubeCarryShiftStateMachine::CubeCarryShiftStateMachine() {
		_cubecarryshiftstate = kScaleShot;
		cubeintaketimer = cubeshiftduration;
	}

	CubeCarryShiftStateMachine::~CubeCarryShiftStateMachine() {
	}
}


