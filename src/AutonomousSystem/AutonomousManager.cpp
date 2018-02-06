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
		_actionselector = new AutoSelector(7); //Number is the port things are in
		_stationselector = new AutoSelector(6);
		//_waitselector = new AutoSelector(4);
		_waitleft = false;
		_waitright = true;
	}

	void AutonomousManager::AutoInit() {
		_gyro->start();
		if (DriverStation::GetInstance().GetAlliance() == DriverStation::kRed) _team = RED;
		else if (DriverStation::GetInstance().GetAlliance() == DriverStation::kBlue) _team = BLUE;
		else _team = NONE;
		_action = _actionselector->getAction();
		_station = _stationselector->getFieldPosition();
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

