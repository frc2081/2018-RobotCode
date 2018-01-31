/*
 * cubecarryshiftstatemachine.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: 1901319
 */

#include <CubeSystem/CubeCarryShiftStateMachine.h>
int cubeintaketimer = 50;
namespace CubeSystem {
	CubeManagerIO  *CubeCarryShiftStateMachine::CubeCarryShiftState(RobotCommands *Command,
			CubeManagerIO *cubeio, IO *RioIO)
	{
		switch(_cubecarryshiftstate)
		{
			case kLowShot:
				cubeio->pokerpos = CubeManagerIO::PokerPosition::EXTENDED;
				if (Command->cmdshiftcube)
				{
					_cubecarryshiftstate = kLowShotToScaleShot;
				}
			break;
			case kLowShotToScaleShot:
				cubeio->pokerpos = CubeManagerIO::PokerPosition::RETRACTED;
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
				cubeio->pokerpos = CubeManagerIO::PokerPosition::RETRACTED;
				if (Command->cmdshiftcube)
				{
					_cubecarryshiftstate = kLowShot;
				}
				break;
		}
		return cubeio;
	}

	CubeCarryShiftStateMachine::CubeCarryShiftStateMachine() {
		// TODO Auto-generated constructor stub
		_cubecarryshiftstate = kLowShot;

	}

	CubeCarryShiftStateMachine::~CubeCarryShiftStateMachine() {
		// TODO Auto-generated destructor stub
	}

}


