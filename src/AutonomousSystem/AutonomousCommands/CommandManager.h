/*
 * CommandManager.h
 *
 *  Created on: Jan 30, 2017
 *      Author: FIRSTUser
 */

#ifndef SRC_AUTOCOMMANDS_COMMANDMANAGER_H_
#define SRC_AUTOCOMMANDS_COMMANDMANAGER_H_

#include <DriveSystem/SwerveLib.h>
#include "CommandIO.h"
#include "CommandBase.h"
#include <queue>
//#include "Calibrations.h"

using namespace std;
class CommandManager {
public:
	CommandManager(robotTeam, robotStation, robotAction, char, char);
	virtual ~CommandManager();
	commandOutput tick(commandInput input);

protected:
	CommandBase *getNextCommand(commandInput input);

private:

	queue<CommandBase*> commands;

	void buildCommands(queue<CommandBase*> *queue,robotTeam, robotStation, robotAction);

	CommandBase *currCommand;

	//replace with Dan's thing later
	void scaleOnly(queue<CommandBase*> *queue,robotTeam team, robotStation station);

	void switchOnly(queue<CommandBase*> *queue,robotTeam team, robotStation station);

	void crossLine(queue<CommandBase*> *queue,robotTeam team, robotStation station);

	double configShooterAng(robotTeam, robotStation);

	double configShooterSpd(robotTeam, robotStation);

	CommandBase *_doNothing;

	char _ourswitch;

	char _scale;
};

#endif /* SRC_AUTOCOMMANDS_COMMANDMANAGER_H_ */
