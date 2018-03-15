/*
 * CommandDrive.h
 *
 *  Created on: Jan 31, 2017
 *      Author: FIRSTUser
 */

#ifndef SRC_AUTOCOMMANDS_COMMANDDRIVE_H_
#define SRC_AUTOCOMMANDS_COMMANDDRIVE_H_
#include "CommandBase.h"
#include "../Gyro/gyroManager.h"

class CommandDrive : public CommandBase {
public:
	//Distance to travel is in imperial units
	CommandDrive(double toTravel, double directon, bool drivestraight);
	virtual ~CommandDrive();

	commandOutput tick(commandInput input);
	void init(commandInput input);
	const char* getCommandName();

protected:
	double checkDistance(commandInput input);
private:

	double LFWhlTurnEncInit;
	double RFWhlTurnEncInit;
	double LBWhlTurnEncInit;
	double RBWhlTurnEncInit;

	double LFWhlDrvEncInit;
	double RFWhlDrvEncInit;
	double LBWhlDrvEncInit;
	double RBWhlDrvEncInit;

	double _toTravel;
	double _direction;
	double _rotcorrection;
	double _gyrohold;
	double _currang;
	bool _drivestraight;
	double _prevdistance;
	gyroManager *_gyro;
	//infinite ducks
};

#endif /* SRC_AUTOCOMMANDS_COMMANDDRIVE_H_ */
