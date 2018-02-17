/*
 * CommandShoot.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: FIRSTUser
 */

#include "CommandShoot.h"
#include <iostream>

CommandShoot::CommandShoot(double fireTimeSec, bool scaleshot, bool switchshot) {
	// TODO Auto-generated constructor stub

	_toWaitSec = fireTimeSec + 2;
	_scale = scaleshot;
	_switch = switchshot;
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

	if (_scale) return commandOutput(true, false);
	else if (_switch) return commandOutput(false, true);
	else return commandOutput(false, false);
}

CommandShoot::~CommandShoot() {
	// TODO Auto-generated destructor stub
}

