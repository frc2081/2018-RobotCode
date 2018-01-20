/*
 * Robot.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_ 1

#include "AutonomousSystem/AutonomousManager.h"
#include "CubeSystem/CubeManager.h"
#include "DriveSystem/DriveManager.h"
#include "RampSystem/RampManager.h"
#include "VisionSystem/VisionManager.h"
#include "Dependencies/SwerveLib.h"
#include "IO.h"

DriveManager *drive;
SwerveLib *swervelib;
IO *io;

#endif /* SRC_ROBOT_H_ */
