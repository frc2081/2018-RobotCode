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
	enum class Cmd {
		CarryShift,
		ScaleShot,
		ExchangeShot,
		SwitchShot,
		IntakeHighShot,
		IntakelowShot,
		Nothing
	};

	//Currently active cube system command
	Cmd currCmd;

};

#endif /* SRC_CUBESYSTEM_CUBEMANAGER_H_ */
