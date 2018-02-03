/*
 * ScaleShotStateMachine.cpp
 *
 *  Created on: Feb 1, 2018
 *      Author: 1901319
 */

#include <CubeSystem/ScaleShotStateMachine.h>
#include "ScaleShotStateMachine.h"
CubeManagerOutputs *ScaleShotStateMachine::ScaleShotStatePeriodic(RobotCommands *Command, CubeManagerInputs *Inputs)
{

	CubeManagerOutputs *cubeio = new CubeManagerOutputs();
	cubeio->isdone = false;
	switch(_scaleshotstate)
	{
	case kwaitingtoshoot:
		// waiting to shoot
		cubeio->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
		cubeio->intakepowercmd = 0;
		cubeio->shooterpowercmd = 0;
		cubeio->shooteranglecmd = 0;
		if(Command->cmdscaleshot){
			_scaleshotstate = kanglingshooter;
		}
		break;
	case kanglingshooter:
		//this state angles arm and spins up the shooter and in take wheels
		//add something to check arm is in right angle before moving on
		cubeio->shooteranglecmd = scaleshotresettimer;
		cubeio->intakepowercmd = motermaxpower;
		cubeio->shooterpowercmd = motermaxpower;
		cubeio->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
		scaleshotwaitingtimer = scaleshotwaitingtimer - 1;
		if(cubeio->shooteranglecmd == placeholderforactualshooterangle && scaleshotwaitingtimer == 0 ){
			_scaleshotstate = kshootingcube;
			scaleshotwaitingtimer = 600;
		}
		break;
	case kshootingcube:
		// this state shoots the cube
		cubeio->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
		cubeio->intakepowercmd = motermaxpower;
		cubeio->shooterpowercmd = motermaxpower;
		cubeio->shooteranglecmd = scaleshotarmangle;
		scaleshotresettimer = scaleshotresettimer - 1;
		if (scaleshotresettimer == 0){
			_scaleshotstate = kreseting;
			scaleshotresettimer = 50;
		}
		break;
	case kreseting:
		// this state turns off the motor and retracts the poker
		cubeio->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
		cubeio->intakepowercmd = 0;
		cubeio->shooterpowercmd = 0;
		cubeio->shooteranglecmd = 0;
		_scaleshotstate = kwaitingtoshoot;
		cubeio->isdone = true;
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

