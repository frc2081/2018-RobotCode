/*
 * RampManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "RampManager.h"
namespace Ramp
{
	RampManager::RampManager(IO *io) {
		_io = io;
		_rampreleasepos = 5000;
		_leftraisetimer = 100;
		_rightraisetimer= 100;
	}

	void RampManager::RampManagerInit() {}
	void RampManager::RampManagerPeriodic(RobotCommands *commands) {
		SmartDashboard::PutBoolean("Ramp Release", commands->cmdramprelease);
		if (!commands->cmdramprelease) return;

		//Move shooter to ramp release position
		_io->shooteranglmot->Set(ControlMode::Position, _rampreleasepos);

		//Raise left ramp
		if (commands->cmdrampraiseleft) {
			--_leftraisetimer;
			if (_leftraisetimer <= 0) {
				_io->ramplmot->Set(0);
			} else _io->ramplmot->Set(1);
		} else _io->ramplmot->Set(0);

		//Raise right ramp
		if (commands->cmdrampraiseright) {
			--_rightraisetimer;
			if (_rightraisetimer <= 0) {
				_io->ramprmot->Set(0);
			} else _io->ramprmot->Set(1);
		} else _io->ramprmot->Set(0);

		//Lower left ramp
		if (commands->cmdramplowerleft) {
			++_rightraisetimer;
			if (_rightraisetimer >= _leftraisetimer) {
				_io->ramprmot->Set(0);
			} else _io->ramprmot->Set(-1);
		} else _io->ramprmot->Set(0);

		//Lower right ramp
		if (commands->cmdramplowerright) {
			++_rightraisetimer;
			if (_rightraisetimer >= _rightraisetimer) {
				_io->ramprmot->Set(0);
			} else _io->ramprmot->Set(-1);
		} else _io->ramprmot->Set(0);
	}
}
