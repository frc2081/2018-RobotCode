/*
 * AutonomousManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_AUTONOMOUSSYSTEM_AUTONOMOUSMANAGER_H_
#define SRC_AUTONOMOUSSYSTEM_AUTONOMOUSMANAGER_H_ 1
#include "AutonomousCommands/CommandManager.h"
#include "Gyro/gyroManager.h"
#include "AutoSelector.h"
#include <IO.h>
#include <RobotCommands.h>

namespace Autonomous
{
	class AutonomousManager {
	public:
		AutonomousManager(IO *io, RobotCommands *commands);

		void AutoPeriodic();

		void AutoInit();

	private:
		robotTeam _team;
		robotStation _station;
		robotAction _action;
		int _actionselector;
		int _stationselector;
		int _waitselector;
		/* These are the ones that our team has */
		char _ourswitch;
		char _scale;
		bool _waitleft;
		bool _waitright;
		bool _buildcommands;
		IO *_io;
		RobotCommands *_commands;
		gyroManager *_gyro;
		CommandManager *_autocommands;
		commandInput _cominput;
		commandOutput _comoutput;
	};
}




#endif /* SRC_AUTONOMOUSSYSTEM_AUTONOMOUSMANAGER_H_ */
