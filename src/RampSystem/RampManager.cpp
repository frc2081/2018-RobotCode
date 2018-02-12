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
		if (commands->cmdramprelease) {
			_io->shooteranglmot->Set(ControlMode::Position, _rampreleasepos);
		}

		if (commands->cmdrampraiseleft) {
			if (_leftraisetimer != 0) {
				_io->ramplmot->Set(1);
				--_leftraisetimer;
			} else _io->ramplmot->Set(0);
		}

		if (commands->cmdrampraiseright) {
			if (_rightraisetimer != 0) {
				_io->ramprmot->Set(1);
				--_leftraisetimer;
			} else _io->ramprmot->Set(0);
		}
	}
}
