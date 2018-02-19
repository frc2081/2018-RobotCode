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
	SmartDashboard::PutNumber("Shooter Dashboard Setpoint: ", shooterStartAngle);

	curShooterAngle = 0;
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
	curShooterAngle = RioIO->shooteranglmot->GetSensorCollection().GetPulseWidthPosition();
	/*Chooses which state machine has control of the IO. If no state machine is in control,
	keeps all outputs set to their last value*/
	//Manual commands
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
				else if ((Commands->cmdintakelowshot || Commands->cmdintakehighshot) && CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::NO_CUBE_PRESENT )
					{ state = STATE::Waitingforcube; }
				else if (Commands->cmdscaleshot && CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT)
					{ state = STATE::Highshotaimandspinup; }
				else if ((Commands->cmdswitchshot || Commands->cmdexchangeshot) && CubeManagerInput->getShooterCubeSensor() == CubeManagerInputs::CubeSensor::CUBE_PRESENT)
					{ state = STATE::Lowshotaim; }
				else if (Commands->cmdresetrobot) { state = STATE::RobotReset; }
				else if (Commands->cmdarmtocarry) { state = STATE::ArmToCarry; }

				highshotentertimer = highShotSpinUpDelay;
				highshotexittimer = highShotShotDuration;
				lowshotexittimer = lowShotShotDuration;
				shifttimer = shiftDuration;
				intakeArmMoveTimer = intakeArmMoveDuration;

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
				CubeManagerOutput->shooteranglecmd = highShotAimAngle;
				//Ramps up the shooter power so roboRio does not brownout
				CubeManagerOutput->intakepowercmd = highShotShooterPower; //- (highshotentertimer / (highShotSpinUpDelay / 2));
				CubeManagerOutput->shooterpowercmd = highShotIntakePower; //- (highshotentertimer / (highShotSpinUpDelay / 2));
				CubeManagerOutput->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;

				--highshotentertimer;

				if(Commands->cmdscaleshot == false) {state = STATE::Idle;}
				else if ((curShooterAngle > highShotAimAngle - highShotAimMargin && curShooterAngle < highShotAimAngle + highShotAimMargin) && highshotentertimer <= 0){
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

			case STATE::ArmToCarry:
				CubeManagerOutput->shooteranglecmd = highShotAimAngle;
				state = STATE::Idle;
				break;


			case STATE::RobotReset:

				if(Commands->cmdresetrobot == false) {
					state = STATE::Idle;
				} else if(CubeManagerInput->armHomeSensor == false) {
					CubeManagerOutput->shooteranglecmd = -10000;
				} else {
					CubeManagerOutput->shooteranglecmd = shooterStartAngle;
					shooterStartAngle = RioIO->shooteranglmot->GetSelectedSensorPosition(0);

					shooterCubePickupAngle = shooterStartAngle + shooterCubePickupAngleOffset;
					highShotAimAngle = shooterStartAngle + highShotAimAngleOffset;
					lowShotAimAngle = shooterStartAngle + lowShotAimAngleOffset;
					exchangeShotAimAngle = shooterStartAngle + exchangeShotAimAngleOffset;
				}

				RobotCommands *reset = new RobotCommands();
				Commands = reset;
				Commands->cmdresetrobot = true;

				break;
		}
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

	double shooterp = SmartDashboard::GetNumber("Shooter P: ", RioIO->armP);
	double shooteri = SmartDashboard::GetNumber("Shooter I: ", RioIO->armI);
	double shooterd = SmartDashboard::GetNumber("Shooter D: ", RioIO->armD);
	RioIO->shooteranglmot->Config_kP(0, shooterp, 0);
	RioIO->shooteranglmot->Config_kI(0, shooteri, 0);
	RioIO->shooteranglmot->Config_kD(0, shooterd, 0);



	//printf("Position: %i Setpoint: %.1f Error: %i Output: %.2f\n", RioIO->shooteranglmot->GetSelectedSensorPosition(0), setpoint, RioIO->shooteranglmot->GetClosedLoopError(0), RioIO->shooteranglmot->GetMotorOutputPercent());
	//printf("Shooter Angle Command: %.1f ShooterStartAngle: %.1f\n", CubeManagerOutput->shooteranglecmd, shooterStartAngle);
	//printf("Intake Sensor: %i Shooter Sensor %i\n", (int)CubeManagerInput->getIntakeCubeSensor(), (int)CubeManagerInput->getShooterCubeSensor());
	RioIO->shooteranglmot->Set(ControlMode::Position, CubeManagerOutput->shooteranglecmd);
	//TODO: Add Angle commands here

	//double setpoint = SmartDashboard::GetNumber("Shooter Dashboard Setpoint: ", 2500);
	//RioIO->shooteranglmot->Set(ControlMode::Position, setpoint);
}
