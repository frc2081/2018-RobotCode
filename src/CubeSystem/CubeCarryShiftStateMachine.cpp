/*
 * cubecarryshiftstatemachine.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: 1901319
 * state machine that switches the location that the cube is being carried
 */

#include <CubeSystem/CubeCarryShiftStateMachine.h>
int cubeintaketimer = 50;
namespace CubeSystem {
// this is the main loop for the cube carry shift state machine
	CubeManagerIO  *CubeCarryShiftStateMachine::CubeCarryShiftStatePeriodic(RobotCommands *Command, IO *RioIO)
	{
		CubeManagerIO *cubeio = new CubeManagerIO();
		switch(_cubecarryshiftstate)
		{
		// state for low carry \ switch shot and exchange shot
			case kLowShot:
				cubeio->pokerpos = CubeManagerIO::PokerPosition::EXTENDED;
				cubeio->isdone = true;
				if (Command->cmdshiftcube)
				{
					_cubecarryshiftstate = kLowShotToScaleShot;
					cubeio->isdone = false;
				}
				break;
			// state for switching low carry to high carry
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
			// state for high carry \ scale shot
			case kScaleShot:
				cubeio->pokerpos = CubeManagerIO::PokerPosition::RETRACTED;
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
		// TODO Auto-generated constructor stub
		_cubecarryshiftstate = kScaleShot;

	}

	CubeCarryShiftStateMachine::~CubeCarryShiftStateMachine() {
		// TODO Auto-generated destructor stub
	}

}


