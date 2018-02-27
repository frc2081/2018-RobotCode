/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <iostream>
#include <IterativeRobot.h>
#include "Robot.h"


class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {

		RioIO = new IO();
		DriverControls = new ControllerManager();
		Commands = new RobotCommands();
		Talons = new TalonConfiguration(RioIO);
		Talons->TalonConfigInit();
		Shooter = new CubeManager(RioIO);
		Shooter->CubeManagerInit();
		Driver = new DriveManager(RioIO, Commands, DriverControls);
		Driver->DriveManagerInit();
		Auto = new Autonomous::AutonomousManager(RioIO, Commands, Shooter);
		Ramps = new Ramp::RampManager(RioIO);
		Ramps->RampManagerInit();
		Vision = new VisionManager();
		//TODO:Add Ramp control system Init
		//TODO:Add Drive System Init
		//TODO:Add Vision System Init, if needed

	}

	void AutonomousInit() override {
		Auto->AutoInit();
	}

	void AutonomousPeriodic() {
		printf("Calling AutoPeriodic\n");
		Auto->AutoPeriodic();
		printf("Calling DriveMangerAutoPeriodic\n");
		Driver->DriveManagerAutoPeriodic();
		Shooter->CubeManagerPeriodic(Commands);
		printf("\n");
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {

		DriverControls->pollControllers(Commands);
		Driver->DriveManagerPeriodic();
		Ramps->RampManagerPeriodic(Commands);
		//TODO:Add polling of sensors!!

		//TODO:Add Drive System Periodic call
		//TODO:Add Vision System Comms Updater, if not multithreade

		Shooter->CubeManagerPeriodic(Commands);
	}

	/* Unused */
	void TestPeriodic() {}

	void DisabledPeriodic() {
		if (!RioIO->swerveresetone->Get() && !RioIO->swerveresettwo->Get()) {
			printf("RESET\n");
			Driver->ZeroEncoders();
		}
	}

	void DisabledInit() {
	}

	void TestInit() {}

	void RobotPeriodic() {}

};

START_ROBOT_CLASS(Robot)
