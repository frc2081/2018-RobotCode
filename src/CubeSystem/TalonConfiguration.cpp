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
	_exchangeheight = 20;
	_switchheight = 40;
	_scaleheight = 60;
	_cntl1 = new cntl(0, 0.2, 0.0);
}

void TalonConfiguration::TalonConfigInit() {
		_io->shooteranglmot->ConfigSelectedFeedbackSensor(
			FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10);
		_io->shooteranglmot->SetStatusFramePeriod(StatusFrame::Status_1_General_, 5, 10); /* Talon will send new frame every 5ms */
		_io->shooteranglmot->SetSensorPhase(_sensorphase);  /* pick this based on your preference on what positive motor output should spin to */
		_io->shooteranglmot->SetInverted(_invert); /* pick this so self-test stops reporting sensor-out-of-phase */
	}

void TalonConfiguration::TalonConfigPeriodic(RobotCommands *command) {//, CubeManagerIO *cubeio) {
		_cntl1->UpdateCntl();
		if (_cntl1->bA->State()) {
			_io->shooteranglmot->SetSelectedSensorPosition(_exchangeheight, 0, 0);
		} else if (_cntl1->bB->State()) {
			_io->shooteranglmot->SetSelectedSensorPosition(_switchheight, 0, 0);
		} else if (_cntl1->bX->State()) {
			_io->shooteranglmot->SetSelectedSensorPosition(_scaleheight, 0, 0);
		} else _io->shooteranglmot->SetSelectedSensorPosition(0, 0, 0);
}

TalonConfiguration::~TalonConfiguration() {
	// TODO Auto-generated destructor stub
}

