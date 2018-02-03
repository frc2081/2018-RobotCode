/*
 * IntakeStateMachine.cpp
 *
 *  Created on: Feb 3, 2018
 *      Author: 1901319
 */
#include <CubeSystem/IntakeStateMachine.h>

 CubeManagerOutputs  *IntakeStateMachine::IntakeStateMachinePeriodic(RobotCommands *Command, CubeManagerInputs *Inputs)
 {
	 CubeManagerOutputs *cubeio = new CubeManagerOutputs();
	 switch(_intakestate)
	 {
	 case kwaitingtopickupcube:
		 cubeio->intakepowercmd = 0;
		 cubeio->shooterpowercmd = 0;
		 cubeio->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::OPEN;
		 if(Inputs->getIntakeCubeSensor() == Inputs->CubeSensor::CUBE_PRESENT){
			 _intakestate = kclosearmarticulation;
		 }
		 break;
	 case kclosearmarticulation:
		 cubeio->intakepowercmd = 0;
		 cubeio->shooterpowercmd = 0;
		 cubeio->shooterArmPos = CubeManagerOutputs::ShooterArmPosition::CLOSED;
		 if(Command->cmdintakehighshot){
			 _intakestate = kscaleshotpickup;
		 }else if(Command->cmdintakelowshot){
			 _intakestate = klowshotpickup;
		 }
		 break;
	 case kscaleshotpickup:
		 cubeio->pokerpos = CubeManagerOutputs::PokerPosition::RETRACTED;
		 cubeio->intakepowercmd = 0.4;
		 cubeio->shooterpowercmd = 0.4;
		 if(Inputs->getShooterCubeSensor() == Inputs->CubeSensor::CUBE_PRESENT){
			 _intakestate = kwaitingtopickupcube;
			 cubeio->isdone = true;
		 }
		 break;
	 case klowshotpickup:
		 cubeio->pokerpos = CubeManagerOutputs::PokerPosition::EXTENDED;
		 cubeio->intakepowercmd = 0.2;
		 cubeio->shooterpowercmd = 0.2;
		 if(Inputs->getShooterCubeSensor() == Inputs->CubeSensor::CUBE_PRESENT){
			 _intakestate = kwaitingtopickupcube;
			 cubeio->isdone = true;
		 }
		 break;
	 }

	 return cubeio;
 }

IntakeStateMachine::IntakeStateMachine() {
	// TODO Auto-generated constructor stub
	_intakestate = kwaitingtopickupcube;
}

IntakeStateMachine::~IntakeStateMachine() {
	// TODO Auto-generated destructor stub
}

