/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <iostream>
#include <IterativeRobot.h>
#include "Robot.h"
#include "IO.h"

class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {

		RioIO = new IO();
		DriverControls = new ControllerManager();

	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {}

	void TeleopPeriodic() {

		DriverControls->pollControllers();

	}

	/* Unused */
	void TestPeriodic() {}

	void DisabledPeriodic() {}

	void DisabledInit() {}

	void TestInit() {}

	void RobotPeriodic() {}

};

START_ROBOT_CLASS(Robot)
