/*
 * ControllerManager.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#include <ControllerInput/ControllerManager.h>
#include "ControllerSettings.h"

ControllerManager::ControllerManager() {
	drivecontroller = new cntl(drivecontrollernumber, drivecontrollerdeadband,drivecontrollerupperlimit);
	mechanismcontroller = new cntl(mechanismcontrollernumber, mechanismcontrollerdeadband, mechanismcontrollerupperlimit);
}

void ControllerManager::pollControllers(){
	drivecontroller->UpdateCntl();
	mechanismcontroller->UpdateCntl();

	//Assisted Cube Intake Command
	if(drivecontroller->bA->State() == true) intakecmd = true;
	else intakecmd = false;


	//TODO: Add command generators
}


