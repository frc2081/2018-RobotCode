/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include <IterativeRobot.h>
#include "Robot.h"

class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {

	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {}

	void TeleopPeriodic() {}

	/* Unused */
	void TestPeriodic() {}

	void DisabledPeriodic() {}

};

START_ROBOT_CLASS(Robot)
