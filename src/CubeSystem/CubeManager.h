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
#include "TalonConfiguration.h"

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
	bool CheckArmHome();

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
		RobotReset,
		ArmToCarry,
	};
	//Currently active cube system command
	STATE state;

	double margin = 400;

	double shooterStartAngle;
	double shooterCubePickupAngleOffset = 300;
	double shooterCubePickupAngle =  300;
	double shooterCubeIntakePower = -.5;
	double armsCubeIntakePower = -.3;

	double highShotAimAngleOffset = -4874;
	double highShotAimAngle =  -4874;
	double highShotAimMargin = margin;
	double highShotShooterPower = .7;
	double highShotIntakePower = .7;
	double highShotSpinUpDelay = 50;
	double highShotShotDuration = 100;

	double lowShotAimAngleOffset = -3571;
	double lowShotAimAngle = -3571;
	double lowShotAimMargin  = margin;
	double lowShotShooterPower = .3;
	double lowShotIntakePower = .3;
	double lowShotShotDuration = 30;

	double exchangeShotAimAngleOffset = -1400;
	double exchangeShotAimAngle = -1400;
	double exchangeShotAimMargin = margin;
	double exchangeShotIntakePower = .4;
	double exchangeShotShooterPower = .4;
	double exchangeShotDuration = 30;

	double shiftDuration = 100;
	double shiftPower = -.5;

	double curShooterAngle;
	int highshotentertimer = highShotSpinUpDelay;
	int highshotexittimer = highShotShotDuration;
	int lowshotexittimer = lowShotShotDuration;
	int shifttimer = shiftDuration;

	int intakeArmMoveDuration = 20;
	int intakeArmMoveTimer = 20;

	bool armHome;
};

#endif /* SRC_CUBESYSTEM_CUBEMANAGER_H_ */
