/*
 * SwitchShotStateMachine.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: 2100433
 */

#include <CubeSystem/SwitchShotStateMachine.h>

SwitchShotStateMachine::SwitchShotStateMachine(){
	switchshotcommand = LOWSHOT_PRESHOT;
	switchshottimer = 300; //placeholder value: how long until switch shot complete from starting wheels
}

CubeManagerIO  *SwitchShotStateMachine::SwitchShotStatePeriodic(RobotCommands *Commands, IO *RioIO)
{
	CubeManagerIO *cubeio = new CubeManagerIO();
	switch (switchshotcommand) { //INITIALIZE THINGS LATER
		case LOWSHOT_PRESHOT:
			//set shooter to low shot angle
			cubeio->shooteranglecmd = 500; //placeholder value: lowshot angle

			//set arms to closed
			cubeio->shooterArmPos = CubeManagerIO::ShooterArmPosition::CLOSED;

			//ensure poker is actually where it should be
			cubeio->pokerpos = CubeManagerIO::PokerPosition::EXTENDED;

			//test for all; switch to shoot when successful
			if((RioIO->shooteranglmot == 500) && (RioIO->shooterangrmot == 500) && (RioIO->shooterarmarticulation == false) && (RioIO->solenoidpoker == true)){
				//all tested values are placeholders
				switchshotcommand = LOWSHOT_SHOOT;
			}

			break;
		case LOWSHOT_SHOOT:
			//set shooting wheels to low speed
			cubeio->shooterpowercmd = 0.3; //placeholder value: low speed shooting

			//wait for shot, then switch to post
			switchshottimer -= 1;
			if(switchshottimer == 0){
				switchshotcommand = LOWSHOT_POSTSHOT;
				switchshottimer = 300; //timer reset
			}

			break;
		case LOWSHOT_POSTSHOT:
			//turn off shooting wheels
			cubeio->shooterpowercmd = 0;

			//set arms to open
			cubeio->shooterArmPos = CubeManagerIO::ShooterArmPosition::OPEN;; //placeholder value: open

			//set shooter to intake angle
			cubeio->shooteranglecmd = 0; //placeholder value: intake angle

			//let things happen; set done
			cubeio->isdone = true;
			switchshotcommand = LOWSHOT_PRESHOT;

			break;
		default:
			//code?
			break;
		}
	return cubeio;
}
