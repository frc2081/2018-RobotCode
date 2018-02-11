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
	state = STATE::Idle;

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
	/*Chooses which state machine has control of the IO. If no state machine is in control,
	keeps all outputs set to their last value*/

	switch(state)
	{
		case STATE::Idle:
			if (Commands->cmdshiftcube && CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::EXTENDED)
				{ state = STATE::shifttohighcarry; }
			else if (Commands->cmdshiftcube && CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::RETRACTED)
				{ state = STATE::Shifttolowcarry; }
			else if ((Commands->cmdintakelowshot || Commands->cmdintakehighshot) && CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::NO_CUBE_PRESENT )
				{ state = STATE::Waitingforcube; }
			else if (Commands->cmdscaleshot && CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT && CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::RETRACTED )
				{ state = STATE::Highshotaimandspinup; }
			else if ((Commands->cmdswitchshot || Commands->cmdexchangeshot) && CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT && CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::EXTENDED)
				{ state = STATE::Lowshotaim; }

			CubeManagerOutput->shooteranglecmd = shooterHomeAngle;
			CubeManagerOutput->shooterpowercmd = 0;
			CubeManagerOutput->intakepowercmd = 0;
			break;

		case STATE::Waitingforcube:
			CubeManagerOutput->shooteranglecmd = shooterCubePickupAngle;
			CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::OPEN;
			CubeManagerOutput->intakepowercmd = armsCubeIntakePower;
			CubeManagerOutput->shooterpowercmd =  shooterCubeIntakePower;

			if(Commands->cmdintakelowshot == false && Commands->cmdintakehighshot == false) {
				state = STATE::Idle;
			}else if (Commands->cmdintakelowshot) {
				CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
			} else if (Commands->cmdintakehighshot) {
				CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
			}

			if (CubeManagerInput->getIntakeCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT) {
				state = STATE::Intakingcube;
			}
			break;

		case STATE::Intakingcube:
			CubeManagerOutput->shooteranglecmd = 0;
			CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
			CubeManagerOutput->intakepowercmd = -0.3;
			CubeManagerOutput->shooterpowercmd = -0.3;
			--intakeexittimer;
			if (intakeexittimer == 0 ||
			CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT)
			{
				state = STATE::Idle;
				intakeexittimer =100;
			}
			break;
		case STATE::Highshotaimandspinup:
			CubeManagerOutput->shooteranglecmd = 75;
			CubeManagerOutput->intakepowercmd = 1;
			CubeManagerOutput->shooterpowercmd = 1;
			CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
			--highshotentertimer;
			if ((int)CubeManagerInput->getShooterAngleActualValue() == (int)CubeManagerOutput->shooteranglecmd &&
			highshotentertimer == 0)
			{
				highshotentertimer = 200;
				state = STATE::Highshot;
			}
			break;
		case STATE::Highshot:
			CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
			--highshotexittimer;
			if(highshotexittimer == 0)
			{
				state = STATE::Idle;
				highshotexittimer = 100;
			}
			break;
		case STATE::Lowshotaim:
			if(Commands->cmdswitchshot)
			{
				CubeManagerOutput->shooteranglecmd = 35;
			}else if (Commands->cmdexchangeshot)
			{
				CubeManagerOutput->shooteranglecmd = 5;
			}
			CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
			if((int)CubeManagerInput->getShooterAngleActualValue() == (int)CubeManagerOutput->shooteranglecmd)
			{
				state = STATE::Lowshot;
			}
			break;
		case STATE::Lowshot:
			CubeManagerOutput->intakepowercmd = 0.5;
			CubeManagerOutput->shooterpowercmd = 0.5;
			--lowshotexittimer;
			if(lowshotexittimer == 0)
			{
				lowshotexittimer = 200;
				state = STATE::Idle;
			}
			break;
		case STATE::Shifttolowcarry:
			CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
			if(CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::EXTENDED)
			{
				state = STATE::Idle;
			}
			break;
		case STATE::shifttohighcarry:
			CubeManagerOutput->intakepowercmd = -0.2;
			CubeManagerOutput->shooterpowercmd = -0.2;
			CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
			if(CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::RETRACTED)
			{
				state = STATE::Idle;
			}
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
