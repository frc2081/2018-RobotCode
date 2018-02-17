
/*
 * CommandDrive.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: FIRSTUser
 */

#include "CommandDrive.h"
#include <stdio.h>

CommandDrive::CommandDrive(double toTravel, double direction, bool drivestraight) {
	// TODO Auto-generated constructor stub
	_toTravel = toTravel;
	_direction = direction;
	_gyro = gyroManager::Get();
	_rotcorrection = 0;
	_drivestraight = drivestraight;
	_gyrohold = _gyro->getLastValue();
}

commandOutput CommandDrive::tick(commandInput input) {
	printf("DRIVING\n");
	if (_drivestraight) {
		if (_gyro->getLastValue()  > 180) {
			_currang - (_gyro->getLastValue() - 360) / 360;
			printf("Correcting by %f\n", _rotcorrection);
		} else _currang = _gyro->getLastValue() / 360;
		_rotcorrection = -_currang * 4;
	} else _rotcorrection = 0;
	if (checkDistance(input) >= _toTravel) {
		setComplete();
		printf("DRIVE COMPLETE\n");
		return doNothing();
	}
	return commandOutput(1, _direction, _rotcorrection);
}

void CommandDrive::init(commandInput input) {

	LFWhlDrvEncInit = input.LFWhlDrvEnc;
	RFWhlDrvEncInit = input.RFWhlDrvEnc;
	LBWhlDrvEncInit = input.LBWhlDrvEnc;
	RBWhlDrvEncInit = input.RBWhlDrvEnc;

	LFWhlTurnEncInit = input.LFWhlTurnEnc;
	RFWhlTurnEncInit = input.RFWhlTurnEnc;
	LBWhlTurnEncInit = input.LBWhlTurnEnc;
	RBWhlTurnEncInit = input.RBWhlTurnEnc;
}

const char* CommandDrive::getCommandName()
{
	return "Drive";
}

double CommandDrive::checkDistance(commandInput input) {

	double LFWhlDrvEnc = fabs(input.LFWhlDrvEnc - LFWhlDrvEncInit);
	double RFWhlDrvEnc = fabs(input.RFWhlDrvEnc - RFWhlDrvEncInit);
	double LBWhlDrvEnc = fabs(input.LBWhlDrvEnc - LBWhlDrvEncInit);
	double RBWhlDrvEnc = fabs(input.RBWhlDrvEnc - RBWhlDrvEncInit);

	double EncAvg = (LFWhlDrvEnc + RFWhlDrvEnc + LBWhlDrvEnc + RBWhlDrvEnc) / 4;

	printf("ENcAvg: %f", EncAvg);

	return EncAvg;

}

CommandDrive::~CommandDrive() {
	// TODO Auto-generated destructor stub
}

