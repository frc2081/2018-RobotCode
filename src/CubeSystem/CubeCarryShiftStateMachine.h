/*
 * cubecarryshiftstatemachine.h
 *
 *  Created on: Jan 26, 2018
 *      Author: 1901319
 */


#ifndef SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_
#define SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_
#include "RobotCommands.h"
#include "IO.h"
#include "CubeManagerIO.h"

namespace CubeSystem {
	class CubeCarryShiftStateMachine {
	public:
		CubeManagerIO *CubeCarryShiftStatePeriodic(RobotCommands *Command, IO *RioIO);
		CubeCarryShiftStateMachine();
		virtual ~CubeCarryShiftStateMachine ();
	private:

		enum CUBECARRYSTATE{
			kLowShot,
			kScaleShot,
			kLowShotToScaleShot,
		};
		CUBECARRYSTATE _cubecarryshiftstate;
	};
}


#endif /* SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_ */
