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
#include "IO.h"
#include "ControllerInput/ControllerManager.h"

IO *RioIO;
ControllerManager *DriverControls;

#endif /* SRC_ROBOT_H_ */
