/*
 * Robot.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_ 1

#include "IO.h"
#include "AutonomousSystem/AutonomousManager.h"
#include "ControllerInput/ControllerManager.h"
#include "CubeSystem/CubeManager.h"
#include "DriveSystem/DriveManager.h"
#include "RampSystem/RampManager.h"
#include "VisionSystem/VisionManager.h"
#include "RobotCommands.h"
#include "CubeSystem/TalonConfiguration.h"
#include "AutonomousSystem/Gyro/gyroManager.h"

IO *RioIO;
ControllerManager *DriverControls;
RobotCommands *Commands;
CubeManager *Shooter;
TalonConfiguration *Talons;
DriveManager *Driver;
Autonomous::AutonomousManager *Auto;
Ramp::RampManager *Ramps;
VisionManager *Vision;

bool autoArmHome;

#endif /* SRC_ROBOT_H_ */
