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
		_actionselector = 0;
		_stationselector = 0;
		_waitleft = false;
		_waitright = true;
		SmartDashboard::PutNumber("Auto Mode", 0);
		SmartDashboard::PutNumber("Auto Station", 0);
		SmartDashboard::PutNumber("Wait Side", 0);
	}

	void AutonomousManager::AutoInit() {
		_gyro->start();
		if (DriverStation::GetInstance().GetAlliance() == DriverStation::kRed) _team = RED;
		else if (DriverStation::GetInstance().GetAlliance() == DriverStation::kBlue) _team = BLUE;
		else _team = NONE;
		_actionselector = SmartDashboard::GetNumber("Auto Mode", 0);
		_stationselector = SmartDashboard::GetNumber("Auto Station", 0);
		_waitselector = SmartDashboard::GetNumber("Wait Side", 0);
		if (_actionselector == 0) _action = SWITCH_SHOT;
		else if (_actionselector == 1) _action = SCALE_SHOT;
		else if (_actionselector == 2) _action = DRIVE_FORWARD;
		else _action = NO_AUTO;

		if (_stationselector == 1) _station = ONE;
		else if (_stationselector == 2) _station = TWO;
		else if (_stationselector == 3) _station = THREE;
		else _station = UNKNOWN;

		if (_waitselector == 0) {
			_waitleft = true;
			_waitright = false;
		}
		else if (_waitselector == 1) {
			_waitright = true;
			_waitleft = false;
		} else {
			_waitleft = false;
			_waitright = false;
		}

		//if (_waitselector->getWaitSide()) {
		//	_waitleft = true;
		//} else _waitright = true;
		//_action = SWITCH_SHOT;
		string scorelocations = DriverStation::GetInstance().GetGameSpecificMessage();
		if (scorelocations.length() >= 2) {
			_ourswitch = scorelocations.at(0);
			_scale = scorelocations.at(1);
		}
		_autocommands = new CommandManager(_team, _station, _action, _ourswitch, _scale, _waitleft, _waitright);
	}

	void AutonomousManager::AutoPeriodic() {
		_cominput.LFWhlDrvEnc = _io->encdrvlf->GetDistance() / 2.54;
		_cominput.RFWhlDrvEnc = _io->encdrvrf->GetDistance() / 2.54;
		_cominput.LBWhlDrvEnc = _io->encdrvlb->GetDistance() / 2.54;
		_cominput.RBWhlDrvEnc = _io->encdrvrb->GetDistance() / 2.54;

		_cominput.LFWhlTurnEnc = _io->steerencdrvlf->Get();
		_cominput.RFWhlTurnEnc = _io->steerencdrvrf->Get();
		_cominput.LBWhlTurnEnc = _io->steerencdrvlb->Get();
		_cominput.RBWhlTurnEnc = _io->steerencdrvrb->Get();

		_cominput.currentGyroReading = _gyro->getLastValue();
		printf("Station: %.2f\n", _station);
		_comoutput = _autocommands->tick(_cominput);

		_commands->drvang = _comoutput.autoAng;
		_commands->drvrot = _comoutput.autoRot;
		_commands->drvmag = _comoutput.autoSpeed;
		_commands->cmdscaleshot = _comoutput.takeScaleShot;
		_commands->cmdswitchshot = _comoutput.takeSwitchShot;
	}
}

