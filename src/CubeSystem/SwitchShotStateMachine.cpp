/*
 * SwitchShotStateMachine.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: 2100433
 */

#include <CubeSystem/SwitchShotStateMachine.h>

SwitchShotStateMachine::SwitchShotStateMachine(){
	switchshotcommand = LOWSHOT_BUTTONCHECK;
	switchshottimer = 300; //placeholder value: how long until switch shot complete from starting wheels
}

CubeManagerOutputs  *SwitchShotStateMachine::SwitchShotStatePeriodic(RobotCommands *Commands, CubeManagerInputs *Inputs)
{
	CubeManagerOutputs *cubeio = new CubeManagerOutputs();
	switch (switchshotcommand) {
		case LOWSHOT_BUTTONCHECK:
			if (Commands->
					cmdswitchshot){
				switchshotcommand = LOWSHOT_PRESHOT;
			}
			break;
		case LOWSHOT_PRESHOT:
			//set shooter to low shot angle
			cubeio->shooteranglecmd = lowshooterangle; //placeholder value: lowshot angle

			//set arms to closed
			cubeio->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;

			//ensure poker is actually where it should be
			cubeio->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;

			//ensure wheels aren't spinning around
			cubeio->shooterpowercmd = noshooterpower;
			cubeio->intakepowercmd = noshooterpower;

			//test for all; switch to shoot when successful
			if((Inputs->getShooterAngleActualValue() >= lowshooterangle - shooteranglemargin) && (Inputs->getShooterAngleActualValue() <= lowshooterangle + shooteranglemargin)){
				//angle test value is placeholder
				switchshotcommand = LOWSHOT_SHOOT;
			}
			//**********TEST PURPOSES ONLY**********
			switchshotcommand = LOWSHOT_SHOOT;
			//**********TEST PURPOSES ONLY**********

			break;
		case LOWSHOT_SHOOT:
			//set shooting wheels to low speed
			cubeio->shooterpowercmd = lowshooterpower; //placeholder value: low speed shooting
			cubeio->intakepowercmd = lowshooterpower;

			//re-setting other values to prevent random dancing from causing problems
			cubeio->shooteranglecmd = lowshooterangle;
			cubeio->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
			cubeio->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;

			//wait for shot, then switch to post
			switchshottimer -= 1; //1 is decrementing the timer
			if(switchshottimer == 0){ //timer finished
				switchshotcommand = LOWSHOT_POSTSHOT;
				switchshottimer = switchshottimerreset; //timer reset
			}

			break;
		case LOWSHOT_POSTSHOT:
			printf("postshot stage\n");
			//turn off shooting wheels
			cubeio->shooterpowercmd = noshooterpower;
			cubeio->intakepowercmd = noshooterpower;

			//set arms to open
			cubeio->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::OPEN;; //placeholder value: open

			//set shooter to intake angle
			cubeio->shooteranglecmd = intakeshooterangle; //placeholder value: intake angle

			//keep poker extended
			cubeio->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;

			//let things happen; set done
			cubeio->isdone = true;
			switchshotcommand = LOWSHOT_BUTTONCHECK;

			break;
		default:
			//code?
			break;
		}
	return cubeio;
}

SwitchShotStateMachine::~SwitchShotStateMachine(){}
