/*
 * CommandTurn.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: FIRSTUser
 */

#include "CommandTurn.h"
#include <iostream>

CommandTurn::CommandTurn(double toRotate) {
	// TODO Auto-generated constructor stub

	_toRotate = toRotate;
	_finalRot = 0;
	currentState = wheelTurn;
}

void CommandTurn::init (commandInput input) {
	//After rotating 720 degrees clockwise (positive), robot will spin in a circle if told to turn that way again
	gyroReadingInit = input.currentGyroReading;

	_finalRot = gyroReadingInit + _toRotate;

	if (_finalRot >= 360) _finalRot -= 360;
	else if (_finalRot < 0) _finalRot += 360;

	if(_toRotate >= 0) _turnDirection = -1;
	else _turnDirection = 1;
}

const char* CommandTurn::getCommandName()
{
	return "Turn";
}

commandOutput CommandTurn::tick(commandInput input) {
	printf("TURNING\n");
	gyroReading = input.currentGyroReading;
	if (gyroReading >= 360) gyroReading = ((int)gyroReading % 360);
	if (gyroReading <= 0) gyroReading = 360 + gyroReading;
	if (gyroReading >= _finalRot - _targetTolerance && gyroReading <= _finalRot + _targetTolerance) {
		setComplete();
		printf("TURN COMPLETE\n");
		return doNothing();
	}

	printf("Target: %f Gyro %f\n", _finalRot, gyroReading );
	return commandOutput(0, 0, (_turnRate * _turnDirection));
}

CommandTurn::~CommandTurn() {
	// TODO Auto-generated destructor stub
}

