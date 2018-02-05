/*
 * CubeManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Dan Wentzel
 */
#include "CubeManager.h"

CubeManager::CubeManager(IO *Output)
{
	CubeManagerInput = new CubeManagerInputs();
	CubeManagerOutput = new CubeManagerOutputs();

	currCmd = Cmd::Nothing;

	RioIO = Output;
}

void CubeManager::CubeManagerInit()
{
	//TODO: Call Init Function of each state machine
}

void CubeManager::CubeManagerPeriodic(RobotCommands *Commands)
{
	//Update all cube system inputs
	CubeManagerInput->updateInputs(RioIO);

	//Chooses which state machine has control of the IO. If no state machine is in control, keeps all outputs set to their last value
	switch(currCmd)
	{
		case Cmd::Nothing:

			if (Commands->cmdshiftcube) { currCmd = Cmd::CarryShift; }
			else if (Commands->cmdintakelowshot) { currCmd = Cmd::IntakelowShot; }
			else if (Commands->cmdscaleshot) { currCmd = Cmd::ScaleShot; }
			else if (Commands->cmdswitchshot) { currCmd = Cmd::SwitchShot; }
			else if (Commands->cmdintakehighshot)  { currCmd = Cmd::IntakeHighShot; }
			else if (Commands->cmdexchangeshot) { currCmd = Cmd::ExchangeShot;  }
			else {currCmd = Cmd::Nothing;}
		break;

		case Cmd::CarryShift:

		break;

		case Cmd::ScaleShot:

		break;

		case Cmd::ExchangeShot:

		break;

		case Cmd::SwitchShot:

		break;

		case Cmd::IntakeHighShot:

		break;

		case Cmd::IntakelowShot:

		break;
	}

}

void CubeManager::AssignIO(CubeManagerOutputs *Commands) {
	RioIO->solenoidpoker->Set(static_cast<bool>(Commands->pokerpos));
	RioIO->shooterarmarticulation->Set(static_cast<bool>(Commands->shooterArmPos));
	RioIO->intakelmot->Set(Commands->intakepowercmd);
	RioIO->intakermot->Set(Commands->intakepowercmd);
	RioIO->shooterlmot->Set(Commands->shooterpowercmd);
	RioIO->shooterrmot->Set(Commands->shooterpowercmd);

	//TODO: Add Angle commands here
}
