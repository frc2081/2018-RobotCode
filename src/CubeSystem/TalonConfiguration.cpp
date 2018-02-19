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
	_talonramptime = .05;
	_ramptimeout = 100;
	printf("Talon Init\n");

	allowableError = 250;
}

void TalonConfiguration::TalonConfigInit() {

		/* lets grab the 360 degree position of the MagEncoder's absolute position */
		int absolutePosition = _io->shooteranglmot->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
		/* use the low level API to set the quad encoder signal */
		_io->shooteranglmot->SetSelectedSensorPosition(absolutePosition, 0, 10);
		_io->shooteranglmot->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10);
		_io->shooteranglmot->SetSensorPhase(false);
		_io->shooteranglmot->ConfigClosedloopRamp(_talonramptime, _ramptimeout);
		_io->shooteranglmot->ConfigAllowableClosedloopError(0, allowableError, 0);

		_io->shooteranglmot->Set(ControlMode::Position, 0);

		/* set the peak and nominal outputs, 12V means full */
		_io->shooteranglmot->ConfigNominalOutputForward(0, 12);
		_io->shooteranglmot->ConfigNominalOutputReverse(0, 12);
		_io->shooteranglmot->ConfigPeakOutputForward(1, 12);
		_io->shooteranglmot->ConfigPeakOutputReverse(-1, 12);

		_io->shooteranglmot->ConfigPeakCurrentLimit(7, 10);
		_io->shooteranglmot->ConfigPeakCurrentDuration(1500, 10);
		_io->shooteranglmot->ConfigContinuousCurrentLimit(2, 10);
		_io->shooteranglmot->EnableCurrentLimit(true);


		/* set closed loop gains in slot0 */
		_io->shooteranglmot->Config_kF(0, 0.0, 0);
		_io->shooteranglmot->Config_kP(0, _io->armP, 0);
		_io->shooteranglmot->Config_kI(0, _io->armI, 0);
		_io->shooteranglmot->Config_kD(0, _io->armD, 0);
	}
TalonConfiguration::~TalonConfiguration() {
	// TODO Auto-generated destructor stub
}

