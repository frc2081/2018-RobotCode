/*
 * CubeManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "CubeManager.h"

CubeManager::CubeManager()
{
	IntakeIO = new CubeManagerIO();
	SwitchShotIO = new CubeManagerIO();
	ScaleShotIO = new CubeManagerIO();
	DeliveryIO = new CubeManagerIO();
	DefaultCommands = new CubeManagerIO();
	//TODO:Instantiate each state machine
}

void CubeManager::CubeManagerInit()
{
	//TODO: Call Init Function of each state machine
}

void CubeManager::CubeManagerPeriodic(RobotCommands *Commands, IO *RioIO)
{

	//TODO:Call periodic function of each state machine, passing each one the command object and IO object
	//if(Commands->intakecmd) { AssignIO(IntakeIO, RioIO); }
	//else (AssignIO(DefaultCommands, RioIO)); //If no state machine is in control, return to the defaults
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
