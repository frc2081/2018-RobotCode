/*
 * IntakeStateMachine.h
 *
 *  Created on: Feb 3, 2018
 *      Author: 1901319
 */

#ifndef SRC_CUBESYSTEM_INTAKESTATEMACHINE_H_
#define SRC_CUBESYSTEM_INTAKESTATEMACHINE_H_
#include "CubeManagerInputs.h"
#include "CubeManagerOutputs.h"
#include "RobotCommands.h"

class IntakeStateMachine {
public:
	CubeManagerOutputs *IntakeStateMachinePeriodic(RobotCommands *Command, CubeManagerInputs *Inputs);
	IntakeStateMachine();
	virtual ~IntakeStateMachine();
private:
	enum INTAKESTATEMACHINE{
		kwaitingtopickupcube,
		kclosearmarticulation,
		klowshotpickup,
		kscaleshotpickup,
			};
	 INTAKESTATEMACHINE _intakestate;


};

#endif /* SRC_CUBESYSTEM_INTAKESTATEMACHINE_H_ */
