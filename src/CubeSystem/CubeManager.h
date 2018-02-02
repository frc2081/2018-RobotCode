/*
 * CubeManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_CUBESYSTEM_CUBEMANAGER_H_
#define SRC_CUBESYSTEM_CUBEMANAGER_H_ 1

#include "ControllerInput/ControllerManager.h"
#include "RobotCommands.h"
#include "IO.h"
#include "CubeManagerIO.h"
#include "CubeCarryShiftStateMachine.h"
#include "ScaleShotStateMachine.h"

class CubeManager
{
public:
	CubeManager();
	void CubeManagerPeriodic(RobotCommands *Commands, IO *RioIO);
	void CubeManagerInit();
	CubeManagerIO *IntakeHighShotIO;
	CubeManagerIO *IntakeLowShotIO;
	CubeManagerIO *SwitchShotIO;
	CubeManagerIO *ScaleShotIO;
	CubeManagerIO *ExchangeShotIO;
	CubeManagerIO *DefaultCommands;
	CubeManagerIO *CubeCarryShiftIO;

	CubeSystem::CubeCarryShiftStateMachine *CubeCarrySwitch;
	ScaleShotStateMachine *ScaleShot;
private:
	void AssignIO(CubeManagerIO *Commands, IO *RioIO);

	enum class Cmd
	{
		CarryShift,
		ScaleShot,
		ExchangeShot,
		SwitchShot,
		IntakeHighShot,
		IntakelowShot,
		Nothing
	};

	Cmd currCmd;
};

#endif /* SRC_CUBESYSTEM_CUBEMANAGER_H_ */
