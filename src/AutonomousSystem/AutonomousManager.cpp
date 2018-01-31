/*
 * AutonomousManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "AutonomousManager.h"
namespace Autonomous
{
	AutonomousManager::AutonomousManager(IO *io, RobotCommands *commands) {
		_io = io;
		_commands = commands;
		_gyro = gyroManager::Get();
	}

	void AutoInit(robotTeam team, robotAction action, robotStation station) {
		_autocommands = new CommandManager(team, action, station);
	}

	void AutonomousManager::AutoPeriodic() {
		_cominput.LFWhlDrvEnc = _io->encdrvlf->Get();
		_cominput.RFWhlDrvEnc = _io->encdrvrf->Get();
		_cominput.LBWhlDrvEnc = _io->encdrvlb->Get();
		_cominput.RBWhlDrvEnc =  _io->encdrvrb->Get();

		_cominput.LFWhlTurnEnc = _io->steerencdrvlf->Get();
		_cominput.RFWhlTurnEnc = _io->steerencdrvrf->Get();
		_cominput.LBWhlTurnEnc = _io->steerencdrvlb->Get();
		_cominput.RBWhlTurnEnc = _io->steerencdrvrb->Get();

		_cominput.currentGyroReading = _gyro->getLastValue();

		_comoutput = _autocommands->tick(_cominput);

		_commands->drvang = _comoutput.autoAng;
		_commands->drvrot = _comoutput.autoRot;
		_commands->drvmag = _comoutput.autoSpeed;
		_commands->cmdscaleshot = _comoutput.takeScaleShot;
		_commands->cmdswitchshot = _comoutput.takeSwitchShot;
	}
}

