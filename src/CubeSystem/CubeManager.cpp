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

	shooterStartAngle = 0;
	shooterStartAngle = Output->shooteranglmot->GetSelectedSensorPosition(0);

	shooterCubePickupAngle = shooterStartAngle + shooterCubePickupAngleOffset;
	highShotAimAngle = shooterStartAngle + highShotAimAngleOffset;
	lowShotAimAngle = shooterStartAngle +lowShotAimAngleOffset;
	exchangeShotAimAngle = shooterStartAngle + exchangeShotAimAngleOffset;

	CubeManagerOutput->shooteranglecmd = shooterStartAngle;
	SmartDashboard::PutNumber("Shooter Home Position: ", shooterStartAngle);
	SmartDashboard::PutNumber("Shooter high shot power: ", highShotShooterPower);
	SmartDashboard::PutNumber("Shooter low shot power: ", lowShotShooterPower);
	SmartDashboard::PutNumber("Shooter exchange shot power: ", exchangeShotShooterPower);
	SmartDashboard::PutNumber("Shooter high shot angle offset: ", highShotAimAngleOffset);
	SmartDashboard::PutNumber("Shooter low shot angle offset: ", lowShotAimAngleOffset);
	SmartDashboard::PutNumber("Shooter exchange shot angle offset: ", exchangeShotAimAngleOffset);

	curShooterAngle = 0;
	RioIO = Output;
}

void CubeManager::CubeManagerInit()
{
	//TODO: Call Init Function of each state machine
}

void CubeManager::CubeManagerPeriodic(RobotCommands *Commands)
{

	highShotShooterPower = SmartDashboard::GetNumber("Shooter high shot power: ", 0);
	highShotIntakePower = SmartDashboard::GetNumber("Shooter high shot power: ", 0);
	lowShotShooterPower = SmartDashboard::GetNumber("Shooter low shot power: ", 0);
	lowShotIntakePower = SmartDashboard::GetNumber("Shooter low shot power: ", 0);
	exchangeShotShooterPower = SmartDashboard::GetNumber("Shooter exchange shot power: ", 0);
	exchangeShotIntakePower = SmartDashboard::GetNumber("Shooter exchange shot power: ", 0);


	RobotCommands *reset = new RobotCommands();


	highShotAimAngle = shooterStartAngle + highShotAimAngleOffset;
	lowShotAimAngle = shooterStartAngle + lowShotAimAngleOffset;
	exchangeShotAimAngle = shooterStartAngle + exchangeShotAimAngleOffset;
	shooterCubePickupAngle = shooterStartAngle + shooterCubePickupAngleOffset;
	highShotMidAimAngle = shooterStartAngle + highShotMidAimAngleOffset;
	highShotHighAimAngle = shooterStartAngle + highShotHighAimAngleOffset;


	//Update all cube system inputs
	CubeManagerInput->updateInputs(RioIO);
	bool scaleShotCommand = (Commands->cmdscaleshot || Commands->cmdscalehighshot || Commands->cmdscalemidshot);

	curShooterAngle = RioIO->shooteranglmot->GetSensorCollection().GetPulseWidthPosition();
	/*Chooses which state machine has control of the IO. If no state machine is in control,
	keeps all outputs set to their last value*/

	if (Commands->cmdisinmechmanual) {
		if (Commands->cmdmanualshooterwheelspos) {
			CubeManagerOutput->shooterpowercmd = 1;
			CubeManagerOutput->intakepowercmd = 1;
		} else if (Commands->cmdmanualshooterwheelsneg) {
			CubeManagerOutput->shooterpowercmd = -1;
			CubeManagerOutput->intakepowercmd = -1;
		} else {
			CubeManagerOutput->shooterpowercmd = 0;
			CubeManagerOutput->intakepowercmd = 0;
		}

		if(Commands->cmdmanualshooterarms) {
			if(CubeManagerOutput->shooterArmPos == CubeManagerOutputs::ShooterArmPosition::OPEN) CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
			else CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::OPEN;
		}
		if(Commands->cmdmanualshooterpoker){
			if(CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::EXTENDED)  CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
			else CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
		}

		if(Commands->cmdmanualshooterangleraise > 0.5) { CubeManagerOutput->shooteranglecmd += 50; }
		else if ( Commands->cmdmanualshooteranglelower > 0.5) { CubeManagerOutput->shooteranglecmd -= 50; }

	} else {
		switch(state)
		{
			case STATE::Idle:
				//CubeManagerOutput->shooteranglecmd = shooterStartAngle;
				CubeManagerOutput->shooterpowercmd = 0;
				CubeManagerOutput->intakepowercmd = 0;

				if (Commands->cmdshiftcube && CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::EXTENDED)
					{ state = STATE::shifttohighcarry; }
				else if (Commands->cmdshiftcube && CubeManagerOutput->pokerpos == CubeManagerOutputs::PokerPosition::RETRACTED)
					{ state = STATE::Shifttolowcarry; }
				else if ((Commands->cmdintakelowshot || Commands->cmdintakehighshot))
					{ state = STATE::Waitingforcube; }
				else if (scaleShotCommand )
					{ state = STATE::Highshotaimandspinup; }
				else if ((Commands->cmdswitchshot || Commands->cmdexchangeshot))
					{ state = STATE::Lowshotaim; }
				else if (Commands->cmdresetrobot) { state = STATE::RobotReset; }
				else if (Commands->cmdarmtocarry) { state = STATE::ArmToCarry; }

				highshotentertimer = highShotSpinUpDelay;
				highshotexittimer = highShotShotDuration;
				lowshotexittimer = lowShotShotDuration;
				shifttimer = shiftDuration;
				intakeArmMoveTimer = intakeArmMoveDuration;

				if(Commands->cmdrampopen) { CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::OPEN;}


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

				if(intakeArmMoveTimer > 0)
				{
					intakeArmMoveTimer--;
				} else if (CubeManagerInput->getIntakeCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT) {
					state = STATE::Intakingcube;
					intakeArmMoveTimer = intakeArmMoveDuration;
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
				if(Commands->cmdscaleshot) {
					CubeManagerOutput->shooteranglecmd = highShotAimAngle;
					CubeManagerOutput->intakepowercmd = highShotShooterPower;
					CubeManagerOutput->shooterpowercmd = highShotIntakePower;
				} else if(Commands->cmdscalehighshot) {
					CubeManagerOutput->shooteranglecmd = highShotHighAimAngle;
					CubeManagerOutput->intakepowercmd = highShotHighShooterPower;
					CubeManagerOutput->shooterpowercmd = highShotHighIntakePower;
				} else if(Commands->cmdscalemidshot) {
					CubeManagerOutput->shooteranglecmd = highShotMidAimAngle;
					CubeManagerOutput->intakepowercmd = highShotMidShooterPower;
					CubeManagerOutput->shooterpowercmd = highShotMidIntakePower;
				}

				//Ramps up the shooter power so roboRio does not brownout
				CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;

				--highshotentertimer;

				if(scaleShotCommand == false) {state = STATE::Idle;}
				else if ((curShooterAngle > CubeManagerOutput->shooteranglecmd - highShotAimMargin && curShooterAngle < CubeManagerOutput->shooteranglecmd + highShotAimMargin) && highshotentertimer <= 0){
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
				} else if (Commands->cmdexchangeshot) {
					CubeManagerOutput->shooteranglecmd = exchangeShotAimAngle;
				}

				if((Commands->cmdswitchshot) &&
					(curShooterAngle > lowShotAimAngle - lowShotAimMargin &&
					 curShooterAngle < lowShotAimAngle + lowShotAimMargin))
				{
					state = STATE::Lowshot;
				} else if (Commands->cmdexchangeshot &&
					(curShooterAngle > exchangeShotAimAngle - exchangeShotAimMargin &&
					curShooterAngle < exchangeShotAimAngle + exchangeShotAimMargin))
				{
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
				state = STATE::Idle;
				break;

			case STATE::shifttohighcarry:
				CubeManagerOutput->intakepowercmd = shiftPower;
				CubeManagerOutput->shooterpowercmd = shiftPower;

				CubeManagerOutput->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;

				if(Commands->cmdshiftcube == false){
					state = STATE::Idle;
					CubeManagerOutput->intakepowercmd = 0;
					CubeManagerOutput->shooterpowercmd = 0;
				}
				break;

			case STATE::ArmToCarry:
				CubeManagerOutput->shooteranglecmd = exchangeShotAimAngle;
				state = STATE::Idle;
				break;

			case STATE::RobotReset:

				if(Commands->cmdresetrobot == false) {
					state = STATE::Idle;
				}
				Commands = reset;
				CubeManagerOutput->shooteranglecmd = 50000;
				break;
		}
	}

	if(intakeArmsFirstCalDone == true && curShooterAngle < shooterStartAngle + intakeArmsClosedOffset )
	{
		CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
	}

	SmartDashboard::PutNumber("Cube State Machine:  ", (int)state);
	SmartDashboard::PutNumber("Intake Sensor:  ", (int)CubeManagerInput->getIntakeCubeSensor());
	SmartDashboard::PutNumber("Shooter Sensor:  ", (int)CubeManagerInput->getShooterCubeSensor());
	//SmartDashboard::PutNumber("Arm SetPoint: ", CubeManagerOutput->shooteranglecmd);
	SmartDashboard::PutNumber("Intake Arm Position", (int)CubeManagerOutput->shooterArmPos);
	SmartDashboard::PutNumber("Arm Current Position", RioIO->shooteranglmot->GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("Arm Motor Current", RioIO->shooteranglmot->GetOutputCurrent());
	SmartDashboard::PutNumber("CubeManager Arm Setpoint", CubeManagerOutput->shooteranglecmd);
	SmartDashboard::PutNumber("Manual Mode", Commands->cmdisinmechmanual);
	SmartDashboard::PutNumber("Poker Position", (int)CubeManagerOutput->pokerpos);

	SmartDashboard::PutNumber("Arm Home Sensor", RioIO->armhomeswitch->Get());
	SmartDashboard::PutNumber("Arm Home Position", shooterStartAngle);

	CheckArmHome();
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



	//printf("Position: %i Setpoint: %.1f Error: %i Output: %.2f\n", RioIO->shooteranglmot->GetSelectedSensorPosition(0), setpoint, RioIO->shooteranglmot->GetClosedLoopError(0), RioIO->shooteranglmot->GetMotorOutputPercent());
	//printf("Shooter Angle Command: %.1f ShooterStartAngle: %.1f\n", CubeManagerOutput->shooteranglecmd, shooterStartAngle);
	//printf("Intake Sensor: %i Shooter Sensor %i\n", (int)CubeManagerInput->getIntakeCubeSensor(), (int)CubeManagerInput->getShooterCubeSensor());
	RioIO->shooteranglmot->Set(ControlMode::Position, CubeManagerOutput->shooteranglecmd);
	//TODO: Add Angle commands here

	//double setpoint = SmartDashboard::GetNumber("Shooter Dashboard Setpoint: ", 2500);
	//RioIO->shooteranglmot->Set(ControlMode::Position, setpoint);
}

bool CubeManager::CheckArmHome()
{
	if(RioIO->shooteranglmot->GetOutputCurrent() > 25 && RioIO->shooteranglmot->GetMotorOutputPercent() > 0)
	{
		shooterStartAngle = RioIO->shooteranglmot->GetSelectedSensorPosition(0);
		armHome = true;
		CubeManagerOutput->shooteranglecmd = shooterStartAngle;
		intakeArmsFirstCalDone = true;
	} else { armHome = false; }

 return armHome;
}

bool CubeManager::SetArmHome()
{
	RioIO->shooteranglmot->Set(ControlMode::Position, 50000);
	if(RioIO->shooteranglmot->GetOutputCurrent() > 25 && RioIO->shooteranglmot->GetMotorOutputPercent() > 0)
	{
		shooterStartAngle = RioIO->shooteranglmot->GetSelectedSensorPosition(0);
		armHome = true;
		CubeManagerOutput->shooteranglecmd = shooterStartAngle;
		intakeArmsFirstCalDone = true;
	} else { armHome = false; }

 return armHome;
}
