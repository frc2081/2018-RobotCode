/*
 * CubeManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Dan Wentzel
 *
 *  This class manages the entire cube system and it's subsystem controls
 *
 *  It calls all cube control subsystem state machines and tracks which one is currently active
 *  The active state machine will have it's desired output written to the actual robot outputs
 *  When the active state is finished, all outputs are held in their last set state until another command is received
 *
 */

#ifndef SRC_CUBESYSTEM_CUBEMANAGER_H_
#define SRC_CUBESYSTEM_CUBEMANAGER_H_ 1

#include <CubeSystem/CubeManagerOutputs.h>
#include "CubeManagerInputs.h"
#include "CubeManagerOutputs.h"
#include "RobotCommands.h"
#include "IO.h"


class CubeManager
{
public:
	CubeManager(IO *Output);
	void CubeManagerPeriodic(RobotCommands *Commands);
	void CubeManagerInit();

	//Object to hold all inputs used by any cube subsystem
	CubeManagerInputs *CubeManagerInput;
	CubeManagerOutputs *CubeManagerOutput;
private:
	//Function that writes the values from a CubeManagerOutputs object to the actual robot outputs
	void AssignIO(CubeManagerOutputs *Commands);

	//Object that contains all robot Inputs and Outputs
	IO *RioIO;

	//Defines all possible cube system commands
	enum class STATE {
		Idle,
		Lowshotaim,
		Lowshot,
		Waitingforcube,
		Intakingcube,
		Shifttolowcarry,
		shifttohighcarry,
		Highshotaimandspinup,
		Highshot,
	};
	//Currently active cube system command
	STATE state;


	bool manualarmsre;
	bool manualarmscurrstate;

	double shooterStartAngle;
	double shooterCubePickupAngle = shooterStartAngle + 4234;
	double shooterCubeIntakePower = -.5;
	double armsCubeIntakePower = -.3;

	double highShotAimAngle = shooterStartAngle - 667;
	double highShotAimMargin = 50;
	double highShotShooterPower = 1;
	double highShotIntakePower = 1;
	double highShotSpinUpDelay = 2;
	double highShotShotDuration = 1;

	double lowShotAimAngle = shooterStartAngle + 3500;
	double lowShotAimMargin  = 50;
	double lowShotShooterPower = .4;
	double lowShotIntakePower = .4;
	double lowShotShotDuration = 30;

	double exchangeShotAimAngle = shooterStartAngle + 4000;
	double exchangeShotAimMargin = 1;
	double exchangeShotIntakePower = .4;
	double exchangeShotShooterPower = .4;
	double exchangeShotDuration = 30;

	double shiftDuration = 30;
	double shiftPower = -.5;

	double curShooterAngle;
	int highshotentertimer = highShotSpinUpDelay;
	int highshotexittimer = highShotShotDuration;
	int lowshotexittimer = lowShotShotDuration;
	int shifttimer = shiftDuration;
};

#endif /* SRC_CUBESYSTEM_CUBEMANAGER_H_ */
