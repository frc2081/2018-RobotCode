/*
 * CubeManagerIO.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#include <CubeSystem/CubeManagerIO.h>

CubeManagerIO::CubeManagerIO() {

	shooterArmPos = ShooterArmPosition::CLOSED;
	pokerpos = PokerPosition::RETRACTED;

	intakepowercmd = 0;
	shooterpowercmd = 0;
	shooteranglecmd = 0;
}
