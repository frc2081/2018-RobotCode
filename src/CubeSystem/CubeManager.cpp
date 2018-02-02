/*
 * CubeManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "CubeManager.h"

CubeManager::CubeManager(IO *Output)
{
	IntakeHighShotIO = new CubeManagerIO();
	IntakeLowShotIO = new CubeManagerIO();
	SwitchShotIO = new CubeManagerIO();
	ScaleShotIO = new CubeManagerIO();
	ExchangeShotIO = new CubeManagerIO();
	DefaultCommands = new CubeManagerIO();
	CubeCarryShiftIO = new CubeManagerIO();
	PreviousIO = new CubeManagerIO();

	CubeCarrySwitch = new CubeSystem::CubeCarryShiftStateMachine();
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
	//Call each periodic function
	CubeCarryShiftIO = CubeCarrySwitch->CubeCarryShiftStatePeriodic(Commands, RioIO);

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
			else { AssignIO(PreviousIO); }
		break;

		case Cmd::CarryShift:
			AssignIO(CubeCarryShiftIO);
			if(CubeCarryShiftIO->isdone) { currCmd = Cmd::Nothing; CubeCarryShiftIO->isdone = false; }
		break;

		case Cmd::ScaleShot:
			AssignIO(ScaleShotIO);
			if(ScaleShotIO->isdone) { currCmd = Cmd::Nothing; ScaleShotIO->isdone = false; }
		break;

		case Cmd::ExchangeShot:
			AssignIO(ExchangeShotIO);
			if(ExchangeShotIO->isdone) { currCmd = Cmd::Nothing; ExchangeShotIO->isdone = false; }
		break;

		case Cmd::SwitchShot:
			AssignIO(SwitchShotIO);
			if(SwitchShotIO->isdone) { currCmd = Cmd::Nothing; SwitchShotIO->isdone = false; }
		break;

		case Cmd::IntakeHighShot:
			AssignIO(IntakeHighShotIO);
			if(IntakeHighShotIO->isdone) { currCmd = Cmd::Nothing; IntakeHighShotIO->isdone = false; }
		break;

		case Cmd::IntakelowShot:
			AssignIO(IntakeLowShotIO);
			if(IntakeLowShotIO->isdone) { currCmd = Cmd::Nothing; IntakeLowShotIO->isdone = false; }
		break;
	}

}

void CubeManager::AssignIO(CubeManagerIO *Commands) {
	RioIO->solenoidpoker->Set(static_cast<bool>(Commands->pokerpos));
	RioIO->shooterarmarticulation->Set(static_cast<bool>(Commands->shooterArmPos));
	RioIO->intakelmot->Set(Commands->intakepowercmd);
	RioIO->intakermot->Set(Commands->intakepowercmd);
	RioIO->shooterlmot->Set(Commands->shooterpowercmd);
	RioIO->shooterrmot->Set(Commands->shooterpowercmd);

	PreviousIO = Commands;
	//TODO: Add Angle commands here
}
