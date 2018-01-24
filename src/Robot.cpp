/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
//#include <iostream>
#include <IterativeRobot.h>
#include "Robot.h"
#include "IO.h"
class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {
		printf("ROBOT STARTING\n");
		swervelib = new SwerveLib(25, 25);
		drive = new DriveManager(swervelib, IO::GetInstance());
		drive->ZeroEncoders();

	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}
	void TeleopInit() {}

	void TeleopPeriodic() {
		drive->CalculateVectors();
		drive->ApplyIntellegintSwerve();
		drive->ApplyPIDControl();
	}

	/* Unused */
	void TestPeriodic() {}

	void DisabledPeriodic() {}

};

START_ROBOT_CLASS(Robot)
