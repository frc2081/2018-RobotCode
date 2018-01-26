/*
 * ControllerManager.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#include <ControllerInput/ControllerManager.h>



ControllerManager::ControllerManager() {
	drivecontroller = new cntl(drivecontrollernumber, drivecontrollerdeadband,drivecontrollerupperlimit);
	mechanismcontroller = new cntl(mechanismcontrollernumber, mechanismcontrollerdeadband, mechanismcontrollerupperlimit);
}

void ControllerManager::pollControllers(RobotCommands *Commands){
	drivecontroller->UpdateCntl();
	mechanismcontroller->UpdateCntl();

	//Assisted Cube Intake Command
	if(drivecontroller->bA->State() == true) Commands->intakecmd = true;
	else Commands->intakecmd = false;


	//TODO: Add command generators
}


