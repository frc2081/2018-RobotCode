/*
 * CubeManagerOutputs.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#include <CubeSystem/CubeManagerOutputs.h>

CubeManagerOutputs::CubeManagerOutputs() {

	shooterArmPos = ShooterArmPosition::CLOSED;
	pokerpos = PokerPosition::RETRACTED;

	intakepowercmd = 0;
	shooterpowercmd = 0;
	shooteranglecmd = 0; //TODO:Replace this with a tune for the default angle of the shooter arm

	isdone = false;
}
