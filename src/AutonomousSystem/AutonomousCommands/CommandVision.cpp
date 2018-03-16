/*
 * CommandVision.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: FIRSTUser
 */

#include "CommandVision.h"

CommandVision::CommandVision(SwerveLib *swerveLib) {
	autoMag = 0;
	autoAng = 0;
	autoRot = 0;
}

void CommandVision::init(commandInput input) {
}

const char* CommandVision::getCommandName()
{
	return "Vision";
}

commandOutput CommandVision::tick(commandInput input) {


	return commandOutput(autoMag, autoAng, autoRot);
}

CommandVision::~CommandVision() {
}

