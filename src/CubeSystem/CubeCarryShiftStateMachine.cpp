/*
 * cubecarryshiftstatemachine.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: 1901319
 */

#include <CubeSystem/CubeCarryShiftStateMachine.h>
int cubeintaketimer = 50;
namespace CubeSystem {

	CubeManagerOutputs  *CubeCarryShiftStateMachine::CubeCarryShiftStatePeriodic(RobotCommands *Command, CubeManagerInputs *Inputs)
	{
		CubeManagerOutputs *cubeio = new CubeManagerOutputs();
		switch(_cubecarryshiftstate)
		{
			case kLowShot:
				cubeio->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
				cubeio->isdone = true;
				if (Command->cmdshiftcube)
				{
					_cubecarryshiftstate = kLowShotToScaleShot;
					cubeio->isdone = false;
				}
				break;

			case kLowShotToScaleShot:
				cubeio->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
				cubeio->intakepowercmd = 0.5;
				cubeio->shooterpowercmd = 0.5;
				cubeintaketimer = cubeintaketimer- 1;

				if (cubeintaketimer == 0)
				{
					_cubecarryshiftstate = kScaleShot;
					cubeintaketimer = 50;
				}
				break;

			case kScaleShot:
				cubeio->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
				cubeio->isdone = true;

				if (Command->cmdshiftcube)
				{
					_cubecarryshiftstate = kLowShot;
					cubeio->isdone = false;
				}
				break;
		}
		return cubeio;
	}

	CubeCarryShiftStateMachine::CubeCarryShiftStateMachine() {
		_cubecarryshiftstate = kScaleShot;
	}

	CubeCarryShiftStateMachine::~CubeCarryShiftStateMachine() {
	}
}


