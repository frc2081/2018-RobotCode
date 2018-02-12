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

	double curShooterAng = CubeManagerInput->getShooterAngleActualValue();
	switch(state)
	{
		case STATE::Idle:
			CubeManagerOutput->shooteranglecmd = shooterHomeAngle;
			CubeManagerOutput->shooterpowercmd = 0;
			CubeManagerOutput->intakepowercmd = 0;

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

			highshotentertimer = highShotSpinUpDelay;
			highshotexittimer = highShotShotDuration;
			lowshotexittimer = lowShotShotDuration;
			shifttimer = shiftDuration;

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
			CubeManagerOutput->shooteranglecmd = shooterCubePickupAngle;
			CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
			CubeManagerOutput->intakepowercmd = armsCubeIntakePower;
			CubeManagerOutput->shooterpowercmd = shooterCubeIntakePower;

			if(Commands->cmdintakelowshot == false && Commands->cmdintakehighshot == false) {
				state = STATE::Idle;
			} else if (Commands->cmdintakelowshot == true && CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT){
				state = STATE::Idle;
			}
			break;

		case STATE::Highshotaimandspinup:
			CubeManagerOutput->shooteranglecmd = highShotAimAngle;
			CubeManagerOutput->intakepowercmd = highShotShooterPower;
			CubeManagerOutput->shooterpowercmd = highShotIntakePower;
			CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;

			--highshotentertimer;

			if(Commands->cmdscaleshot == false) {state = STATE::Idle;}
			else if ((curShooterAng > highShotAimAngle - highShotAimMargin && curShooterAng < highShotAimAngle + highShotAimMargin) && highshotentertimer <= 0){
				highshotentertimer = highShotSpinUpDelay;
				state = STATE::Highshot;
			}
			break;

		case STATE::Highshot:
			CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
			--highshotexittimer;
			if(highshotexittimer <= 0){
				state = STATE::Idle;
				highshotexittimer = highShotShotDuration;
			}
			break;

		case STATE::Lowshotaim:
			CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
			if(Commands->cmdswitchshot == false && Commands->cmdexchangeshot == false) {
				state = STATE::Idle;
			} else if(Commands->cmdswitchshot) {
				CubeManagerOutput->shooteranglecmd = lowShotAimAngle;
			}else if (Commands->cmdexchangeshot) {
				CubeManagerOutput->shooteranglecmd = exchangeShotAimAngle;
			}

			if(Commands->cmdswitchshot && (curShooterAng > lowShotAimAngle - lowShotAimMargin && curShooterAng < lowShotAimAngle + lowShotAimMargin)) {
				state = STATE::Lowshot;
			}
			break;

		case STATE::Lowshot:

			--lowshotexittimer;
			if(Commands->cmdswitchshot)
			{
				CubeManagerOutput->intakepowercmd = lowShotIntakePower;
				CubeManagerOutput->shooterpowercmd = lowShotShooterPower;
				if(lowshotexittimer <= 0){
					lowshotexittimer = lowShotShotDuration;
					state = STATE::Idle;
				}
			} else if (Commands->cmdexchangeshot) {
				CubeManagerOutput->intakepowercmd = exchangeShotIntakePower;
				CubeManagerOutput->shooterpowercmd = exchangeShotShooterPower;
				if(lowshotexittimer <= 0){
					lowshotexittimer = exchangeShotDuration;
					state = STATE::Idle;
				}
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
			CubeManagerOutput->intakepowercmd = shiftPower;
			CubeManagerOutput->shooterpowercmd = shiftPower;

			--shifttimer;
			CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
			if(shifttimer <= shiftDuration)
			{
				shifttimer = shiftDuration;
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
