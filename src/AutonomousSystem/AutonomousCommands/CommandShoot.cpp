/*
 * CommandShoot.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: FIRSTUser
 */

#include "CommandShoot.h"
#include <iostream>

CommandShoot::CommandShoot(double fireTimeSec) {
	_toWaitSec = fireTimeSec + 2;
}

void CommandShoot::init(commandInput input) {
	_initTime = time(NULL);
}

const char* CommandShoot::getCommandName()
{
	return "Shoot";
}

commandOutput CommandShoot::tick(commandInput input) {
	time_t currentTime = time(NULL);

	time_t elapsed = currentTime - _initTime;

	printf("Shooting...\n");

	//if (elapsed <= 1) return commandOutput(0,0,0, true, false);

	if (_toWaitSec >= 0 && elapsed >= _toWaitSec) {
		setComplete();
		return doNothing();
	}

	return commandOutput(true, false);
}

CommandShoot::~CommandShoot() {
}

