/*
 * CommandTurn.h
 *
 *  Created on: Jan 31, 2017
 *      Author: FIRSTUser
 */

#ifndef SRC_AUTOCOMMANDS_COMMANDTURN_H_
#define SRC_AUTOCOMMANDS_COMMANDTURN_H_
#include "CommandBase.h"

class CommandTurn : public CommandBase {
public:
	CommandTurn(double toRotate);
	virtual ~CommandTurn();

	commandOutput tick(commandInput input);
	void init(commandInput input);
	const char* getCommandName();

protected:
	double checkRotation(commandInput input);

	enum currentActivity {
		wheelTurn,
		driveMot
	};
private:

	currentActivity currentState;

	double _toRotate;
	double _finalRot = 0;

	double gyroReadingInit = NULL;

	double gyroReading = NULL;

	double _toTravel = 0;

	double _turnDirection = 1; //positive = clockwise, negative = counterClockwise;
	double _turnRate = 0.4; //radians per sec
	double _targetTolerance = 5; //maximum allowed delta from target angle to consider turn complete

	//infinite ducks
};

#endif /* SRC_AUTOCOMMANDS_COMMANDTURN_H_ */
