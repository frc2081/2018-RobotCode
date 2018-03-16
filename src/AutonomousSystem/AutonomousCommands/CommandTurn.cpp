/*
 * CommandTurn.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: FIRSTUser
 */

#include "CommandTurn.h"
#include <iostream>

CommandTurn::CommandTurn(double toRotate) {
	_toRotate = toRotate;
	currentState = wheelTurn;
}

double _BoundFinalRot(double finalrot) {
	if (finalrot >= 360)   finalrot -= 360;
	else if (finalrot < 0) finalrot += 360;

	if(finalrot >= 360)   return _BoundFinalRot(finalrot);
	else if(finalrot < 0) return _BoundFinalRot(finalrot);

	return finalrot;
}

void CommandTurn::init (commandInput input) {
	//After rotating 720 degrees clockwise (positive), robot will spin in a circle if told to turn that way again
	// ^ This is because the >= 360 check wass only performed once. This bug is now fixed
	gyroReadingInit = input.currentGyroReading;

	_finalRot = gyroReadingInit + _toRotate;

	// This should fix the spinning bug
	_finalRot = _BoundFinalRot(_finalRot);

	if(_toRotate >= 0) _turnDirection = 1;
	else _turnDirection = -1;
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
}

