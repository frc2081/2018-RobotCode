/*
 * CommandManager.cpp
 *
 *  Created on: Jan 30, 2017
 *      Author: FIRSTUser
 */

#include "CommandManager.h"
#include "CommandDrive.h"
#include "CommandPause.h"
#include "CommandTurn.h"
#include "CommandVision.h"
#include "CommandShoot.h"
#include <stdio.h>

CommandManager::CommandManager(robotTeam team, robotStation station, robotAction action, char ourswitch, char scale, bool waitleft, bool waitright) {

	_ourswitch = ourswitch;
	_scale = scale;
	_waitleft = waitleft;
	_waitright = waitright;

	commands = queue<CommandBase*>();
	buildCommands(&commands, team, station, action);

	commands.push(_doNothing = new CommandPause(-1));
	currCommand = NULL;
}

commandOutput CommandManager::tick(commandInput input) {

	if (currCommand == NULL || currCommand->isDone())
		currCommand = getNextCommand(input);

	return currCommand == NULL
		? commandOutput()
		: currCommand->tick(input);
}

void CommandManager::scaleOnly(queue<CommandBase*> *queue,robotTeam team, robotStation station) {
	/* ALL NUMBERS ARE PLACEHOLDERS UNTIL THE TRUE ONES ARE MEASURED */
	if (_scale == 'L') {
		//if (team == RED) {
			queue->push(new CommandDrive(5, 0, true));
			if (station == ONE) {
				queue->push(new CommandDrive(250, 0, true));
				queue->push(new CommandTurn(90));
			} else if (station == THREE) {
				queue->push(new CommandDrive(125, 0, true));
				queue->push(new CommandDrive(200, 270, true));
				queue->push(new CommandDrive(40, 0, true));
				queue->push(new CommandTurn(90));
			} else if(station == TWO) {
				if (_waitleft) {
					queue->push(new CommandPause(3));
					queue->push(new CommandDrive(40, 90, true));
					queue->push(new CommandDrive(130, 0, true));
					queue->push(new CommandTurn(90));
				} else if (_waitright) {
					queue->push(new CommandPause(3));
					queue->push(new CommandDrive(40, 270, true));
					queue->push(new CommandDrive(130, 0, true));
					queue->push(new CommandDrive(150, 90, true));
					queue->push(new CommandDrive(40, 0, true));
					queue->push(new CommandTurn(90));
				}
			}
			queue->push(new CommandShoot(10, true, false));
		/* else if (team == BLUE) {
			if (station == THREE) {
				queue->push(new CommandDrive(80, 0));
				queue->push(new CommandTurn(-90));
				queue->push(new CommandShoot(10));
			} else if (station == ONE) {
				queue->push(new CommandDrive(40, 0));
				queue->push(new CommandDrive(160, 90));
				queue->push(new CommandDrive(40, 0));
				queue->push(new CommandTurn(-90));
				queue->push(new CommandShoot(10));
			} else if (station == TWO) {
				if (_waitleft) {
					queue->push(new CommandPause(3));
					queue->push(new CommandDrive(40, 270));
					queue->push(new CommandDrive(130));
					queue->push(new CommandTurn(90));
				} else if (_waitright) {
					queue->push(new CommandPause(3));
					queue->push(new CommandDrive(40, 90));
					queue->push(new CommandDrive(130));
					queue->push(new CommandDrive(150, 270));
					queue->push(new CommandDrive(40, 0));
					queue->push(new CommandTurn(90));
				}
			}
		} */
	} else if (_scale == 'R') {

		if (team == RED) {
			queue->push(new CommandDrive(5, 0, true));
			if (station == THREE) {
				queue->push(new CommandDrive(80, 0, true));
				queue->push(new CommandTurn(-90));
			} else if (station == ONE) {
				queue->push(new CommandDrive(40, 0, true));
				queue->push(new CommandDrive(160, 90, true));
				queue->push(new CommandDrive(40, 0, true));
				queue->push(new CommandTurn(-90));
			} else if (station == TWO) {
				if (_waitright) {
					queue->push(new CommandPause(3));
					queue->push(new CommandDrive(40, 90, true));
					queue->push(new CommandDrive(130, 0, true));
					queue->push(new CommandTurn(-90));
				} else if (_waitleft) {
					queue->push(new CommandPause(3));
					queue->push(new CommandDrive(40, 270, true));
					queue->push(new CommandDrive(130, 0, true));
					queue->push(new CommandDrive(150, 90, true));
					queue->push(new CommandDrive(40, 0, true));
					queue->push(new CommandTurn(-90));
				}
			}
		}/* else if (team == BLUE) {
			if (station == ONE) {
				queue->push(new CommandDrive(80, 0));
				queue->push(new CommandTurn(90));
				queue->push(new CommandShoot(10));
			} else if (station == THREE) {
				queue->push(new CommandDrive(40, 0));
				queue->push(new CommandDrive(160, 270));
				queue->push(new CommandDrive(40, 0));
				queue->push(new CommandTurn(90));
			}

		}*/
		queue->push(new CommandShoot(10, true, false));
	}
}

void CommandManager::switchOnly(queue<CommandBase*> *queue,robotTeam team, robotStation station) {
	if (_ourswitch == 'L') {
		printf("LEFT\n");
		if (station == TWO) {
			queue->push(new CommandDrive(40, 45, true));
		} else if (station == ONE) {
			queue->push(new CommandDrive(40, 0, true));
			queue->push(new CommandTurn(90));
			queue->push(new CommandDrive(10, 0, false));
		} else if (station == THREE) {
			queue->push(new CommandDrive(130, 0, true));
			queue->push(new CommandDrive(130, 270, true));
			queue->push(new CommandTurn(180));
			queue->push(new CommandDrive(10, 0, false));
		}
	} else if (_ourswitch == 'R') {
		printf("RIGHT\n");
		if (station == TWO) {
			queue->push(new CommandDrive(90, 45, true));
		} else if (station == ONE) {
			queue->push(new CommandDrive(130, 0, true));
			queue->push(new CommandDrive(130, 90, true));
			queue->push(new CommandTurn(180));
			queue->push(new CommandDrive(10, 0, false));
		} else if (station == THREE) {
			queue->push(new CommandDrive(40, 0, true));
			queue->push(new CommandTurn(-90));
			queue->push(new CommandDrive(10, 0, false));
		}
	}
	queue->push(new CommandShoot(10, false, true));
}

void CommandManager::crossLine(queue<CommandBase*> *queue,robotTeam team, robotStation station) {
	queue->push(new CommandDrive(40, 0, true));
}

CommandBase *CommandManager::getNextCommand(commandInput input) {

	// In the event that all prior commands have been popped off the queue, do nothing.
	if (commands.size() < 1)
		return _doNothing;

	CommandBase *nextCommand =  commands.front();
	commands.pop();

	//Need to add NULL protection here in case no command was added to the queue prior to the pop
	if (currCommand != NULL) delete currCommand;

	if(nextCommand == NULL)
	{
		printf("Received a null command from the queue.\n");
		return _doNothing;
	}

	printf("Retrieved a %s Command from the queue.\n", nextCommand->getCommandName());
	nextCommand->init(input);
	printf("Command Init Successful\n");
	return nextCommand;
}

void CommandManager::buildCommands(queue<CommandBase*> *queue, robotTeam team, robotStation station, robotAction action) {
	switch(action) {
	case SWITCH_SHOT:
		switchOnly(queue, team, station);
		break;
	case SCALE_SHOT:
		scaleOnly(queue, team, station);
		break;
	case DRIVE_FORWARD:
		crossLine(queue, team, station);
		break;
	default:
		break;
	}
	queue->push(new CommandPause(-1));
}

double CommandManager::configShooterSpd(robotTeam team, robotStation RS)
{
	double shooterSpd = 0;
	if(team == robotTeam::RED)
	{
		if(RS == ONE) shooterSpd = 3000;
		else if (RS == TWO) shooterSpd = 3900;
		else if (RS == THREE) shooterSpd = 4600;
	} else {
		if(RS == THREE) shooterSpd = 3000;
		else if (RS == TWO) shooterSpd = 3900;
		else if (RS == ONE) shooterSpd = 4600;
	}

	return shooterSpd;
 }

double CommandManager::configShooterAng(robotTeam team, robotStation RS)
{
	double shooterAng = 0;
	if(team == robotTeam::RED)
	{
		if(RS == ONE) shooterAng = .4;
		else if (RS == TWO) shooterAng = .6;
		else if (RS == THREE) shooterAng = 1;
	} else {
		if(RS == THREE) shooterAng = .4;
		else if (RS == TWO) shooterAng = .6;
		else if (RS == ONE) shooterAng = 1;
	}

	return shooterAng;
}

CommandManager::~CommandManager() {
	// TODO Auto-generated destructor stub
}

