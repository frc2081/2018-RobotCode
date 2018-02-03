/*
 * CubeManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Dan Wentzel
 */
#include "CubeManager.h"

CubeManager::CubeManager(IO *Output)
{
	IntakeHighShotOutput = new CubeManagerOutputs();
	IntakeLowShotOutput = new CubeManagerOutputs();
	SwitchShotOutput = new CubeManagerOutputs();
	ScaleShotOutput = new CubeManagerOutputs();
	ExchangeShotOutput = new CubeManagerOutputs();
	CubeCarryShiftOutput = new CubeManagerOutputs();
	PreviousOutput = new CubeManagerOutputs();

	CubeManagerInput = new CubeManagerInputs();

	CubeCarrySwitch = new CubeSystem::CubeCarryShiftStateMachine();
	ScaleShot = new ScaleShotStateMachine();
	//TODO:Instantiate each state machine

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

	//Call each periodic function
	CubeCarryShiftOutput = CubeCarrySwitch->CubeCarryShiftStatePeriodic(Commands, CubeManagerInput);
	ScaleShotIO = ScaleShot->ScaleShotStatePeriodic(Commands, RioIO);

	//Chooses which state machine has control of the IO. If no state machine is in control, keeps all outputs set to their last value

	switch(currCmd)
	{
		case Cmd::Nothing:
			if (Commands->cmdshiftcube) currCmd = Cmd::CarryShift;
			else if (Commands->cmdintakelowshot) currCmd = Cmd::IntakelowShot;
			else if (Commands->cmdscaleshot) currCmd = Cmd::ScaleShot;
			else if (Commands->cmdswitchshot) currCmd = Cmd::SwitchShot;
			else if (Commands->cmdintakehighshot) currCmd = Cmd::IntakeHighShot;
			else if (Commands->cmdexchangeshot) currCmd = Cmd::ExchangeShot;
			else { AssignIO(PreviousOutput); }
		break;

		case Cmd::CarryShift:
			AssignIO(CubeCarryShiftOutput);
			if(CubeCarryShiftOutput->isdone) { currCmd = Cmd::Nothing; CubeCarryShiftOutput->isdone = false; }
		break;

		case Cmd::ScaleShot:
			AssignIO(ScaleShotOutput);
			if(ScaleShotOutput->isdone) { currCmd = Cmd::Nothing; ScaleShotOutput->isdone = false; }
		break;

		case Cmd::ExchangeShot:
			AssignIO(ExchangeShotOutput);
			if(ExchangeShotOutput->isdone) { currCmd = Cmd::Nothing; ExchangeShotOutput->isdone = false; }
		break;

		case Cmd::SwitchShot:
			AssignIO(SwitchShotOutput);
			if(SwitchShotOutput->isdone) { currCmd = Cmd::Nothing; SwitchShotOutput->isdone = false; }
		break;

		case Cmd::IntakeHighShot:
			AssignIO(IntakeHighShotOutput);
			if(IntakeHighShotOutput->isdone) { currCmd = Cmd::Nothing; IntakeHighShotOutput->isdone = false; }
		break;

		case Cmd::IntakelowShot:
			AssignIO(IntakeLowShotOutput);
			if(IntakeLowShotOutput->isdone) { currCmd = Cmd::Nothing; IntakeLowShotOutput->isdone = false; }
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

	PreviousOutput = Commands;
	//TODO: Add Angle commands here
}
