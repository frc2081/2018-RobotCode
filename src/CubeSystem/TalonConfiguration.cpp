/*
 * TalonConfiguration.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: support
 */

#include <CubeSystem/TalonConfiguration.h>

TalonConfiguration::TalonConfiguration(IO *io) {
	_io = io;
	_sensorphase = false;
	_invert = true;
	_exchangeheight = 1000;
	_switchheight = 2000;
	_scaleheight = 3000;
	_cntl1 = new cntl(0, 0.2, 0.0);
}

void TalonConfiguration::TalonConfigInit() {
		/* lets grab the 360 degree position of the MagEncoder's absolute position */
		int absolutePosition = _io->shooteranglmot->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
		/* use the low level API to set the quad encoder signal */
		_io->shooteranglmot->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10);
		_io->shooteranglmot->SetSelectedSensorPosition(absolutePosition, 0, 0);
		_io->shooteranglmot->SetSensorPhase(true);

		/* set the peak and nominal outputs, 12V means full */
		_io->shooteranglmot->ConfigNominalOutputForward(0, 10);
		_io->shooteranglmot->ConfigNominalOutputReverse(0, 10);
		_io->shooteranglmot->ConfigPeakOutputForward(1, 10);
		_io->shooteranglmot->ConfigPeakOutputReverse(-1, 10);

		/* set closed loop gains in slot0 */
		_io->shooteranglmot->Config_kF(0, 0.0, 0);
		_io->shooteranglmot->Config_kP(0, 0.1, 0);
		_io->shooteranglmot->Config_kI(0, 0.0, 0);
		_io->shooteranglmot->Config_kD(0, 0.0, 0);
	}

void TalonConfiguration::TalonConfigPeriodic(RobotCommands *command) {//, CubeManagerIO *cubeio) {
		_cntl1->UpdateCntl();
		if (_cntl1->bA->State()) {
			_io->shooteranglmot->Set(ctre::phoenix::motorcontrol::ControlMode::Position, _exchangeheight);
		} else if (_cntl1->bB->State()) {
			_io->shooteranglmot->Set(ctre::phoenix::motorcontrol::ControlMode::Position, _switchheight);
		} else if (_cntl1->bX->State()) {
			_io->shooteranglmot->Set(ctre::phoenix::motorcontrol::ControlMode::Position, _scaleheight);
		} else _io->shooteranglmot->Set(ctre::phoenix::motorcontrol::ControlMode::Position, 0);
}

TalonConfiguration::~TalonConfiguration() {
	// TODO Auto-generated destructor stub
}

