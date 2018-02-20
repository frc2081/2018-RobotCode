/*
 * RampManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_RAMPSYSTEM_RAMPMANAGER_H_
#define SRC_RAMPSYSTEM_RAMPMANAGER_H_ 1
#include "IO.h"
#include "RobotCommands.h"
namespace Ramp {

	class RampManager {
	public:
		RampManager(IO *io);

		void RampManagerInit();

		void RampManagerPeriodic(RobotCommands *commands);

	private:
		IO *_io;

		double _rampreleasepos;

		double _leftraisetimer;
		double _rightraisetimer;
		double _rampOpenTimer;
	};
}




#endif /* SRC_RAMPSYSTEM_RAMPMANAGER_H_ */
