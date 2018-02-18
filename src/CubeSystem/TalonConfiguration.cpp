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
}

void TalonConfiguration::TalonConfigInit() {
		printf("Talon config start\n");
		/* lets grab the 360 degree position of the MagEncoder's absolute position */
		int absolutePosition = _io->shooteranglmot->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
		printf("Got shooter sensor\n");
		/* use the low level API to set the quad encoder signal */
		_io->shooteranglmot->SetSelectedSensorPosition(absolutePosition, 0, 10);
		printf("Sensor selected\n");
		_io->shooteranglmot->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 10);
		printf("Sensor configured\n");
		_io->shooteranglmot->SetSensorPhase(false);
		printf("Set sensor phase\n");
		_io->shooteranglmot->ConfigClosedloopRamp(_talonramptime, _ramptimeout);
		_io->shooteranglmot->ConfigAllowableClosedloopError(0, 300, 0);
		printf("Closed loop ramp configured\n");

		_io->shooteranglmot->Set(ControlMode::Position, 0);

		/* set the peak and nominal outputs, 12V means full */
		_io->shooteranglmot->ConfigNominalOutputForward(0, 12);
		_io->shooteranglmot->ConfigNominalOutputReverse(0, 12);
		_io->shooteranglmot->ConfigPeakOutputForward(1, 12);
		_io->shooteranglmot->ConfigPeakOutputReverse(-1, 12);

		/* set closed loop gains in slot0 */
		_io->shooteranglmot->Config_kF(0, 0.0, 0);
		_io->shooteranglmot->Config_kP(0, 1.4, 0);
		_io->shooteranglmot->Config_kI(0, 0, 0);
		_io->shooteranglmot->Config_kD(0, 0.0, 0);
		printf("Talon config end\n");
	}
TalonConfiguration::~TalonConfiguration() {
	// TODO Auto-generated destructor stub
}

