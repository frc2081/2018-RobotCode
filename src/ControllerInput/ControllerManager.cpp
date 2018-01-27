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
	//Trigger Activation Threshold
	double trigactivthreshold = 0.6;

	//Driver Controls

	//Drive Commands

	//Ramp Release Command
	if(drivecontroller->bStart->State() == true && drivecontroller->bBack->State() == true) Commands->cmdramprelease = true;
	else Commands->cmdramprelease = false;

	//Left Ramp Raise Command
	if(drivecontroller->LTrig >= trigactivthreshold) Commands->cmdrampraiseleft = true;
	else Commands->cmdrampraiseleft = false;

	//Right Ramp Raise Command
	if(drivecontroller->RTrig >= trigactivthreshold) Commands->cmdrampraiseright = true;
	else Commands->cmdrampraiseright = false;

	//Automatic Cube Intake Command
	if(drivecontroller->bA->State() == true) Commands->cmdautopickup = true;
	else Commands->cmdautopickup = false;


	//Manipulator Controls
	if(mechanismcontroller->bLS->Held() == true){
		//Manual Mode

		//Raise Shooter Angle Command
		Commands->cmdmanualshooterangleraise = mechanismcontroller->LTrig;

		//Lower Shooter Angle Command
		Commands->cmdmanualshooteranglelower = mechanismcontroller->RTrig;

		//Shooter Wheels Command
		if(mechanismcontroller->bA->State() == true) Commands->cmdmanualshooterwheels = true;
		else Commands->cmdmanualshooterwheels = false;

		//Shooter Arms Command
		if(mechanismcontroller->bB->RE() == true) Commands->cmdmanualshooterarms = true;
		else Commands->cmdmanualshooterarms = false;

		//Shooter Poker Command
		if(mechanismcontroller->bX->State() == true) Commands->cmdmanualshooterpoker = true;
		else Commands->cmdmanualshooterpoker = false;
	}

	else{
		//High Shot Intake Command
		if(mechanismcontroller->RTrig >= trigactivthreshold) Commands->cmdintakehighshot = true;
		else Commands->cmdintakehighshot = false;

		//Low Shot Intake Command
		if(mechanismcontroller->LTrig >= trigactivthreshold) Commands->cmdintakelowshot = true;
		else Commands->cmdintakelowshot = false;

		//Scale Shot Command
		if(mechanismcontroller->bX->State() == true) Commands->cmdscaleshot = true;
		else Commands->cmdscaleshot = false;

		//Switch Shot Command
		if(mechanismcontroller->bY->State() == true) Commands->cmdswitchshot = true;
		else Commands->cmdswitchshot = false;

		//Exchange Shot Command
		if(mechanismcontroller->bB->State() == true) Commands->cmdexchangeshot = true;
		else Commands->cmdexchangeshot = false;

		//Shift Cube Carry Position Command
		if(mechanismcontroller->bA->State() == true) Commands->cmdshiftcube = true;
		else Commands->cmdshiftcube = false;

		//Automatic Scale Shot Command
		if(mechanismcontroller->bLB->State() == true && mechanismcontroller->bRB->State() == true) Commands->cmdautoscaleshot = true;
		else Commands->cmdautoscaleshot = false;


	}
	//

	//TODO: Add command generators
}


