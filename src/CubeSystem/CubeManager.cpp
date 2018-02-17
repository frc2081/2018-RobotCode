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

	manualarmsre = false;
	manualarmscurrstate = false;

	RioIO = Output;
	SmartDashboard::PutNumber("Current shooter angle", 0);
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
	SmartDashboard::PutNumber("State machine state: ", (double)state);
	SmartDashboard::PutNumber("Intake power: ", CubeManagerOutput->intakepowercmd);
	SmartDashboard::PutBoolean("State done? ", CubeManagerOutput->isdone);
	SmartDashboard::PutNumber("Poker position: ", (double)CubeManagerOutput->pokerpos);
	SmartDashboard::PutNumber("Shooter arm position: ", (double)CubeManagerOutput->shooterArmPos);
	SmartDashboard::PutNumber("Shooter angle command", CubeManagerOutput->shooteranglecmd);
	SmartDashboard::PutNumber("Shooter power command", CubeManagerOutput->shooterpowercmd);
	SmartDashboard::PutNumber("Cube Shooter present: ", (double)CubeManagerInput->getShooterCubeSensor());
	SmartDashboard::PutNumber("Cube Intake present: ", (double)CubeManagerInput->getIntakeCubeSensor());
	SmartDashboard::PutBoolean("High intake command", Commands->cmdintakehighshot);
	SmartDashboard::PutBoolean("Low intake command", Commands->cmdintakelowshot);
	SmartDashboard::PutNumber("Low shot aim angle", lowShotAimAngle);
	curShooterAng = SmartDashboard::GetNumber("Current shooter angle", 0);
	//Manual commands
	if (Commands->cmdisinmechmanual) {
		RioIO->shooteranglmot->Set(ControlMode::PercentOutput, Commands->cmdmanualshooterangleraise - Commands->cmdmanualshooteranglelower);
		if (Commands->cmdmanualshooterwheelspos) {
			RioIO->shooterlmot->Set(1);
			RioIO->shooterlmot->Set(1);
			RioIO->intakelmot->Set(1);
			RioIO->intakermot->Set(1);
		} else if (Commands->cmdmanualshooterwheelsneg) {
			RioIO->shooterlmot->Set(-1);
			RioIO->shooterlmot->Set(-1);
			RioIO->intakelmot->Set(-1);
			RioIO->intakermot->Set(-1);
		} else {
			RioIO->shooterlmot->Set(0);
			RioIO->shooterlmot->Set(0);
			RioIO->intakelmot->Set(0);
			RioIO->intakermot->Set(0);
		}
		if (Commands->cmdmanualshooterarms == true && manualarmsre == false) {
			RioIO->shooterarmarticulationopen->Set(!manualarmscurrstate);
			RioIO->shooterarmarticulationclose->Set(manualarmscurrstate);
			manualarmscurrstate = !manualarmscurrstate;
		}
		RioIO->solenoidpokeropen->Set(Commands->cmdmanualshooterpoker);
		RioIO->solenoidpokerclose->Set(!Commands->cmdmanualshooterpoker);
		manualarmsre = Commands->cmdmanualshooterarms;
	} else {
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
				} else if ((Commands->cmdintakelowshot || Commands->cmdintakehighshot) == true && CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT){
					state = STATE::Idle;
				}
				break;

			case STATE::Highshotaimandspinup:
				CubeManagerOutput->shooteranglecmd = highShotAimAngle;
				//Ramps up the shooter power so roboRio does not brownout
				CubeManagerOutput->intakepowercmd = highShotShooterPower - (highshotentertimer / highShotSpinUpDelay);
				CubeManagerOutput->shooterpowercmd = highShotIntakePower - (highshotentertimer / highShotSpinUpDelay);
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
					lowShotAimAngle = 35;
				}else if (Commands->cmdexchangeshot) {
					CubeManagerOutput->shooteranglecmd = exchangeShotAimAngle;
					lowShotAimAngle = 5;
				}

				if((Commands->cmdswitchshot || Commands->cmdexchangeshot) && (curShooterAng > lowShotAimAngle - lowShotAimMargin && curShooterAng < lowShotAimAngle + lowShotAimMargin)) {
					state = STATE::Lowshot;
				}
				break;

			case STATE::Lowshot:

				--lowshotexittimer;
				if(Commands->cmdswitchshot)
				{
					CubeManagerOutput->intakepowercmd = lowShotIntakePower;
					CubeManagerOutput->shooterpowercmd = lowShotShooterPower;

				} else if (Commands->cmdexchangeshot) {
					CubeManagerOutput->intakepowercmd = exchangeShotIntakePower;
					CubeManagerOutput->shooterpowercmd = exchangeShotShooterPower;
				}
				if(lowshotexittimer <= 0){
					lowshotexittimer = lowShotShotDuration;
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
	AssignIO(CubeManagerOutput);
}


void CubeManager::AssignIO(CubeManagerOutputs *Commands) {
	RioIO->solenoidpokeropen->Set(static_cast<bool>(Commands->pokerpos));
	RioIO->solenoidpokerclose->Set(!static_cast<bool>(Commands->pokerpos));
	RioIO->shooterarmarticulationopen->Set(static_cast<bool>(Commands->shooterArmPos));
	RioIO->shooterarmarticulationclose->Set(!static_cast<bool>(Commands->shooterArmPos));
	RioIO->intakelmot->Set(Commands->intakepowercmd);
	RioIO->intakermot->Set(Commands->intakepowercmd);
	RioIO->shooterlmot->Set(Commands->shooterpowercmd);
	RioIO->shooterrmot->Set(Commands->shooterpowercmd);

	//TODO: Add Angle commands here
}
