/*
 * ScaleShotStateMachine.cpp
 *
 *  Created on: Feb 1, 2018
 *      Author: 1901319
 */

#include <CubeSystem/ScaleShotStateMachine.h>
#include <ScaleShotStateMachine.h>
CubeManagerIO *ScaleShotStateMachine::ScaleShotStatePeriodic(RobotCommands *Command, IO *RioIO)
{

	CubeManagerIO *cubeio = new CubeManagerIO();
	cubeio->isdone = true;
	switch(_scaleshotstate)
	{
	case kwaitingtoshoot:
		cubeio->pokerpos = CubeManagerIO::PokerPosition::RETRACTED;
		cubeio->intakepowercmd = 0;
		cubeio->shooterpowercmd = 0;
		cubeio->shooteranglecmd = 0;
		if(Command->cmdscaleshot){
			_scaleshotstate = kanglingshooter;
		}
		break;
	case kanglingshooter:
		//add something to check arm is in right angle before moving on
		cubeio->shooteranglecmd = 75;
		cubeio->intakepowercmd = 1;
		cubeio->shooterpowercmd = 1;
		cubeio->pokerpos = CubeManagerIO::PokerPosition::RETRACTED;
		scaleshotwaitingtimer = scaleshotwaitingtimer - 1;
		if(cubeio->shooteranglecmd == placeholderforactualshooterangle && scaleshotwaitingtimer == 0 ){
			_scaleshotstate = kshootingcube;
			scaleshotwaitingtimer = 600;
		}
		break;
	case kshootingcube:
		cubeio->pokerpos = CubeManagerIO::PokerPosition::EXTENDED;
		cubeio->intakepowercmd = 1;
		cubeio->shooterpowercmd = 1;
		cubeio->shooteranglecmd = 75;
		scaleshotresettimer = scaleshotresettimer - 1;
		if (scaleshotresettimer == 0){
			_scaleshotstate = kwaitingtoshoot;
			scaleshotresettimer = 50;
			cubeio->isdone = false;
		}
	}
	return cubeio;
}

ScaleShotStateMachine::ScaleShotStateMachine() {
	// TODO Auto-generated constructor stub
	_scaleshotstate = kwaitingtoshoot;
}

ScaleShotStateMachine::~ScaleShotStateMachine() {
	// TODO Auto-generated destructor stub
}

