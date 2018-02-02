/*
 * CubeManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "CubeManager.h"

CubeManager::CubeManager()
{
	IntakeHighShotIO = new CubeManagerIO();
	IntakeLowShotIO = new CubeManagerIO();
	SwitchShotIO = new CubeManagerIO();
	ScaleShotIO = new CubeManagerIO();
	ExchangeShotIO = new CubeManagerIO();
	DefaultCommands = new CubeManagerIO();
	CubeCarryShiftIO = new CubeManagerIO();

	CubeCarrySwitch = new CubeSystem::CubeCarryShiftStateMachine();
	ScaleShot = new ScaleShotStateMachine();
	//TODO:Instantiate each state machine

	currCmd = Cmd::Nothing;
}

void CubeManager::CubeManagerInit()
{
	//TODO: Call Init Function of each state machine
}

void CubeManager::CubeManagerPeriodic(RobotCommands *Commands, IO *RioIO)
{
	//Call each periodic function
	CubeCarryShiftIO = CubeCarrySwitch->CubeCarryShiftStatePeriodic(Commands, RioIO);
	ScaleShotIO = ScaleShot->ScaleShotStatePeriodic(Commands, RioIO);
	switch(currCmd)
	{
		case Cmd::Nothing:
			if (Commands->cmdshiftcube) currCmd = Cmd::CarryShift;
			else if (Commands->cmdintakelowshot) currCmd = Cmd::IntakelowShot;
			else if (Commands->cmdscaleshot) currCmd = Cmd::ScaleShot;
			else if (Commands->cmdswitchshot) currCmd = Cmd::SwitchShot;
			else if (Commands->cmdintakehighshot) currCmd = Cmd::IntakeHighShot;
			else if (Commands->cmdexchangeshot) currCmd = Cmd::ExchangeShot;
			else currCmd = Cmd::Nothing;
		break;

		case Cmd::CarryShift:
			AssignIO(CubeCarryShiftIO, RioIO);
			if(CubeCarryShiftIO->isdone) { currCmd = Cmd::Nothing; CubeCarryShiftIO->isdone = false; }
		break;

		case Cmd::ScaleShot:
			AssignIO(ScaleShotIO, RioIO);
			if(ScaleShotIO->isdone) { currCmd = Cmd::Nothing; ScaleShotIO->isdone = false; }
		break;

		case Cmd::ExchangeShot:
			AssignIO(ExchangeShotIO, RioIO);
			if(ExchangeShotIO->isdone) { currCmd = Cmd::Nothing; ExchangeShotIO->isdone = false; }
		break;

		case Cmd::SwitchShot:
			AssignIO(SwitchShotIO, RioIO);
			if(SwitchShotIO->isdone) { currCmd = Cmd::Nothing; SwitchShotIO->isdone = false; }
		break;

		case Cmd::IntakeHighShot:
			AssignIO(IntakeHighShotIO, RioIO);
			if(IntakeHighShotIO->isdone) { currCmd = Cmd::Nothing; IntakeHighShotIO->isdone = false; }
		break;

		case Cmd::IntakelowShot:
			AssignIO(IntakeLowShotIO, RioIO);
			if(IntakeLowShotIO->isdone) { currCmd = Cmd::Nothing; IntakeLowShotIO->isdone = false; }
		break;
	}

}

void CubeManager::AssignIO(CubeManagerIO *Commands, IO *RioIO) {
	RioIO->solenoidpoker->Set(static_cast<bool>(Commands->pokerpos));
	RioIO->shooterarmarticulation->Set(static_cast<bool>(Commands->shooterArmPos));
	RioIO->intakelmot->Set(Commands->intakepowercmd);
	RioIO->intakermot->Set(Commands->intakepowercmd);
	RioIO->shooterlmot->Set(Commands->shooterpowercmd);
	RioIO->shooterrmot->Set(Commands->shooterpowercmd);
	//TODO: Add Angle commands here
}
