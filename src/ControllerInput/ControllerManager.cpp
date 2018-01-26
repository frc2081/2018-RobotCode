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

	//TODO: Add command generators
}


