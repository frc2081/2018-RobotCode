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
		_rampOpenTimer = 200;
	}

	void RampManager::RampManagerInit() {}
	void RampManager::RampManagerPeriodic(RobotCommands *commands) {
		SmartDashboard::PutBoolean("Ramp Release", commands->cmdramprelease);
		SmartDashboard::PutNumber("Servo angle: ", _io->ramprelease->GetAngle());
		_io->ramprelease->SetAngle(0);
		if (!commands->cmdramprelease) return;

		--_rampOpenTimer;
		//if(_rampOpenTimer <= 0) { commands->cmdrampopen = true;}

		_io->ramprelease->SetAngle(180);

		//Raise left ramp

		printf("Ramp Command\n");
		if (commands->cmdrampraiseleft) {_io->ramplmot->Set(-1);
		} else if (commands->cmdramplowerleft) {_io->ramplmot->Set(1);}
		else _io->ramplmot->Set(0);

		if (commands->cmdrampraiseright) {_io->ramprmot->Set(-1);
		} else if (commands->cmdramplowerright) {_io->ramprmot->Set(1);}
		else _io->ramprmot->Set(0);
	}
}
