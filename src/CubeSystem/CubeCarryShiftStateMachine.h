/*
 * cubecarryshiftstatemachine.h
 *
 *  Created on: Jan 26, 2018
 *      Author: 1901319
 */


#ifndef SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_
#define SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_
#include <CubeSystem/CubeManagerOutputs.h>
#include "CubeManagerInputs.h"
#include "RobotCommands.h"


namespace CubeSystem {
	class CubeCarryShiftStateMachine {
	public:
		CubeManagerOutputs *CubeCarryShiftStatePeriodic(RobotCommands *Command, CubeManagerInputs *Inputs);
		CubeCarryShiftStateMachine();
		virtual ~CubeCarryShiftStateMachine ();
	private:

		enum CUBECARRYSTATE{
			kLowShot,
			kScaleShot,
			kLowShotToScaleShot,
		};
		CUBECARRYSTATE _cubecarryshiftstate;
		int cubeintaketimer;

		//*********************CALIBRATIONS********************
		const int cubeshiftduration = 50;
		const double cubecarryshiftintakepower = 0.5;
		const double cubecarryshiftshooterpower = 0.5;

	};
}


#endif /* SRC_CUBESYSTEM_CUBECARRYSHIFTSTATEMACHINE_H_ */
