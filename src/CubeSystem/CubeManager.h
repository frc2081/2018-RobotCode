/*
 * CubeManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_CUBESYSTEM_CUBEMANAGER_H_
#define SRC_CUBESYSTEM_CUBEMANAGER_H_ 1

#include <CubeSystem/CubeManagerOutputs.h>
#include "RobotCommands.h"
#include "IO.h"
#include "CubeCarryShiftStateMachine.h"

class CubeManager
{
public:
	CubeManager(IO *Output);
	void CubeManagerPeriodic(RobotCommands *Commands);
	void CubeManagerInit();
	CubeManagerOutputs *IntakeHighShotIO;
	CubeManagerOutputs *IntakeLowShotIO;
	CubeManagerOutputs *SwitchShotIO;
	CubeManagerOutputs *ScaleShotIO;
	CubeManagerOutputs *ExchangeShotIO;
	CubeManagerOutputs *CubeCarryShiftIO;

	CubeSystem::CubeCarryShiftStateMachine *CubeCarrySwitch;

private:
	void AssignIO(CubeManagerOutputs *Commands);

	IO *RioIO;

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
	CubeManagerOutputs *PreviousIO;
};

#endif /* SRC_CUBESYSTEM_CUBEMANAGER_H_ */
