/*
 * AutonomousManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "AutonomousManager.h"
namespace Autonomous
{
	AutonomousManager::AutonomousManager(IO *io, RobotCommands *commands, CubeManager *cube) {
		_io = io;
		_commands = commands;
		_actionselector = 0;
		_stationselector = 0;
		_waitleft = false;
		_waitright = true;
		_buildcommands = true;
		_fielddata = "";
		_polltimer = 100;
		_cube = cube;
		_gyro = gyroManager::Get();
		//_action = NONE;
		//_ourswitch = '';
		//_scale = '';
		//_station = NONE;
		_team = NONE;
		SmartDashboard::PutNumber("Auto Mode", 0);
		SmartDashboard::PutNumber("Auto Station", 0);
		SmartDashboard::PutNumber("Wait Side", 0);
	}

	void AutonomousManager::AutoInit() {
		printf("Starting auto\n");
		_gyro->start();

		_fielddata = DriverStation::GetInstance().GetGameSpecificMessage();
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

		//Building commands in periodic to make sure the most up to date values are obtained
		//for more information, visit http://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details

	}

	void AutonomousManager::AutoPeriodic() {
		printf("Entering Autoperiodic\n\n");
		//if (_cube->armHome == false) _io->shooteranglmot->Set(ControlMode::Position, 50000);
		if (!_cube->armHome) _cube->SetArmHome();
		if(_buildcommands) {
			_fielddata = DriverStation::GetInstance().GetGameSpecificMessage();
			printf("Checking for data\n");
			if (_fielddata.length() > 0) {
					if (_fielddata.length() >= 2) {
						_ourswitch = _fielddata.at(0);
						_scale = _fielddata.at(1);
					}
					printf("Building commands\n");
					_autocommands = new CommandManager(_team, _station, _action, _ourswitch, _scale, _waitleft, _waitright);
					_buildcommands = false;
			}
		}
		_cominput.LFWhlDrvEnc = _io->encdrvlf->GetDistance() / 100;
		_cominput.RFWhlDrvEnc = _io->encdrvrf->GetDistance() / 100;
		_cominput.LBWhlDrvEnc = _io->encdrvlb->GetDistance() / 100;
		_cominput.RBWhlDrvEnc = _io->encdrvrb->GetDistance() / 100;

		_cominput.LFWhlTurnEnc = _io->steerencdrvlf->Get();
		_cominput.RFWhlTurnEnc = _io->steerencdrvrf->Get();
		_cominput.LBWhlTurnEnc = _io->steerencdrvlb->Get();
		_cominput.RBWhlTurnEnc = _io->steerencdrvrb->Get();

		_cominput.currentGyroReading = _gyro->getLastValue();
		//printf("Gyro value %.2f", _gyro->getLastValue());
		_comoutput = _autocommands->tick(_cominput);
		//printf("Ticked\n");

		//printf("Magnitude: %.2f  Angle: %.2f  Rotation: %.2\n", _commands->drvmag, _commands->drvang, _commands->drvrot);
		//printf("LFDrive: %.2f  RFDrive: %.2f  LBDrive: %.2f, RBDrive: %.2f\n", _io->drvlfmot->Get(), _io->drvrfmot->Get(), _io->drvlbmot->Get(), _io->drvrbmot->Get());
		_commands->drvang = _comoutput.autoAng;
		_commands->drvrot = _comoutput.autoRot;
		_commands->drvmag = _comoutput.autoSpeed;
		_commands->cmdscaleshot = _comoutput.takeScaleShot;
		_commands->cmdswitchshot = _comoutput.takeSwitchShot;
	}
}

