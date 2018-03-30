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
	printf("building\n");
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
	queue->push(new CommandShoot(0.5, false, false, true));
	//queue->push(new CommandDrive(.5, 0, false));
	if (_scale == 'L') {
		if (station == ONE) {
			queue->push(new CommandDrive(7.5, 0, false));
			queue->push(new CommandTurn(70));
			queue->push(new CommandDrive(.46, 180, false));
		} else if (station == THREE) {
			queue->push(new CommandDrive(5.5, 0, false));
			queue->push(new CommandDrive(6.68, 90, false));
			queue->push(new CommandDrive(2.26, 0, false));
			queue->push(new CommandTurn(-70));
			queue->push(new CommandDrive(.15, 180, false));
		} else if(station == TWO) {
			if (_waitleft) {
				queue->push(new CommandPause(3));
				queue->push(new CommandDrive(3.5, 90, false));
				queue->push(new CommandDrive(6, 0, false));
				queue->push(new CommandTurn(-70));
			} else if (_waitright) {
				queue->push(new CommandPause(3));
				queue->push(new CommandDrive(3, 270, false));
				queue->push(new CommandDrive(5.5, 0, false));
				queue->push(new CommandDrive(6.5, 90, false));
				queue->push(new CommandDrive(2, 0, false));
				queue->push(new CommandTurn(-70));
			}
		}
	} else if (_scale == 'R') {
		if (station == THREE) {
			queue->push(new CommandDrive(7.5, 0, false));
			queue->push(new CommandTurn(-70));
			queue->push(new CommandDrive(.46, 180, false));
		} else if (station == ONE) {
			queue->push(new CommandDrive(5.5, 0, false));
			queue->push(new CommandDrive(6.68, 270, false));
			queue->push(new CommandDrive(2.26, 0, false));
			queue->push(new CommandTurn(70));
			queue->push(new CommandDrive(.15, 0, false));
		} else if (station == TWO) {
			if (_waitright) {
				queue->push(new CommandPause(3));
				queue->push(new CommandDrive(3, 270, false));
				queue->push(new CommandDrive(7.5, 0, false));
				queue->push(new CommandTurn(70));
			} else if (_waitleft) {
				queue->push(new CommandPause(3));
				queue->push(new CommandDrive(1.75, 0, false));
				queue->push(new CommandDrive(3.5, 90, false));
				queue->push(new CommandDrive(3, 0, false));
				queue->push(new CommandDrive(6, 270, false));
				queue->push(new CommandDrive(3.25, 0, false));
				queue->push(new CommandTurn(70));
			}
		}
	}
	queue->push(new CommandShoot(10, true, false, false));
}

void CommandManager::switchOnly(queue<CommandBase*> *queue,robotTeam team, robotStation station) {
	queue->push(new CommandShoot(0.5, false, false, true));
	if (_ourswitch == 'L') {
		printf("LEFT\n");
		if (station == TWO) {
			queue->push(new CommandDrive(1.75, 45, false));
			//queue->push(new CommandDrive(1.5, 90, false));
			queue->push(new CommandDrive(.75, 0, false));
		} else if (station == ONE) {
			queue->push(new CommandDrive(3.5, 0, false));
			queue->push(new CommandTurn(90));
			queue->push(new CommandDrive(0.3, 0, false));
		} else if (station == THREE) {
			queue->push(new CommandDrive(5.2, 0, false));
			queue->push(new CommandDrive(4, 90, false));
			queue->push(new CommandTurn(180));
			queue->push(new CommandDrive(0.254, 0, false));
		}
	} else if (_ourswitch == 'R') {
		printf("RIGHT\n");
		if (station == TWO) {
			queue->push(new CommandDrive(1.75, 315, false));
			queue->push(new CommandDrive(.75, 0, false));
		} else if (station == ONE) {
			queue->push(new CommandDrive(5.2, 0, false));
			queue->push(new CommandDrive(4, 270, false));
			queue->push(new CommandTurn(180));
			queue->push(new CommandDrive(0.254, 0, false));
		} else if (station == THREE) {
			queue->push(new CommandDrive(3.5, 0, false));
			queue->push(new CommandTurn(-90));
			queue->push(new CommandDrive(0.27, 0, false));
		}
	}
	queue->push(new CommandShoot(10, false, true, false));
}

void CommandManager::crossLine(queue<CommandBase*> *queue,robotTeam team, robotStation station) {
	queue->push(new CommandDrive(2.5, 0, true));
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
	printf("Built\n");
	//queue->push(new CommandDrive(1, 0, false));
	//queue->push(new CommandDrive(.1, 90, false));
	//queue->push(new CommandTurn(90));
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

