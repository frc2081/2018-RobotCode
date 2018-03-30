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
		//Set raising solenoid to be down unless being commanded up
		_io->solenoidraisehookopen->Set(false);
		_io->solenoidraisehookclose->Set(true);
		if (!commands->cmdramprelease) return;
		//Raise hook
		_io->solenoidraisehookopen->Set(true);
		_io->solenoidraisehookclose->Set(false);

		//Right bumper raise winch
		if (commands->cmdrampraiseright) {
			_io->ramplmot->Set(1);
			//Unsure if one or two motor controllers running winch
			_io->ramprmot->Set(1);
		}

		/*
		 * Code for ramps, no longer on robot
		 * 	_io->ramprelease->SetAngle(0);
		 * _io->ramprelease->SetAngle(180);
		printf("Ramp Command\n");
		if (commands->cmdrampraiseleft) {_io->ramplmot->Set(-1);
		} else if (commands->cmdramplowerleft) {_io->ramplmot->Set(1);}
		else _io->ramplmot->Set(0);

		if (commands->cmdrampraiseright) {_io->ramprmot->Set(-1);
		} else if (commands->cmdramplowerright) {_io->ramprmot->Set(1);}
		else _io->ramprmot->Set(0);
		*/
	}
}
