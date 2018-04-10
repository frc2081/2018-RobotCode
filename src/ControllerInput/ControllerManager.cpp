/*
 * ControllerManager.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#include <ControllerInput/ControllerManager.h>
#include <math.h>



ControllerManager::ControllerManager() {
	drivecontroller = new cntl(drivecontrollernumber, drivecontrollerdeadband,drivecontrollerupperlimit);
	mechanismcontroller = new cntl(mechanismcontrollernumber, mechanismcontrollerdeadband, mechanismcontrollerupperlimit);
}

void ControllerManager::pollControllers(RobotCommands *Commands){

	drivecontroller->UpdateCntl();
	mechanismcontroller->UpdateCntl();

	//Drive Commands
	Commands->drvang = (atan2(-drivecontroller->LX, drivecontroller->LY) * 180/3.14159265);
	Commands->drvmag = sqrt(pow(drivecontroller->LX, 2) + pow(drivecontroller->LY, 2));
	Commands->drvrot = drivecontroller->RX;
	//Ramp Release Command
	if(drivecontroller->bA->State()) Commands->cmdramprelease = true;
	else Commands->cmdramprelease = false;

	//Left Ramp Raise Command
	if(drivecontroller->bLB->State()) Commands->cmdrampraiseleft = true;
	else Commands->cmdrampraiseleft = false;

	//Right Ramp Raise Command
	if(drivecontroller->bRB->State() && drivecontroller->bStart->State()&& drivecontroller->bBack->State()) Commands->cmdwinch = true;
	else Commands->cmdwinch = false;

	//Left Ramp Lower Command
	if (drivecontroller->bX->State()) Commands->cmdramplowerleft = true;
	else Commands->cmdramplowerleft = false;

	//Right Ramp Lower Command
	if (drivecontroller->bB->State()) Commands->cmdramplowerright = true;
	else Commands->cmdramplowerright = false;

	//Automatic Cube Intake Command
	//if(drivecontroller->bA->State() == true) Commands->cmdautopickup = true;
	//else Commands->cmdautopickup = false;

	//Arm to carry position - duplicated for ease of driving
	if(drivecontroller->bY->State()) Commands->cmdarmtocarry = true;
	else Commands->cmdarmtocarry = false;

	//Manipulator Controls
	if(mechanismcontroller->bLS->Held() == true){

		manualModeDeactivationTimer = manualModeDeactivationDelay;
		//Manual Mode
		Commands->cmdisinmechmanual = true;
		//Raise Shooter Angle Command
		Commands->cmdmanualshooterangleraise = (double)mechanismcontroller->bLB->State();

		//Lower Shooter Angle Command
		Commands->cmdmanualshooteranglelower = (double)mechanismcontroller->bRB->State();

		//Shooter Wheels Command Positive
		if(mechanismcontroller->bA->State() == true) Commands->cmdmanualshooterwheelspos = true;
		else Commands->cmdmanualshooterwheelspos = false;

		//Shooter Wheels Command Negative
		if (mechanismcontroller->bB->State() == true) Commands->cmdmanualshooterwheelsneg = true;
		else Commands->cmdmanualshooterwheelsneg = false;

		//Shooter Arms Command
		if(mechanismcontroller->bX->RE() == true) Commands->cmdmanualshooterarms = true;
		else Commands->cmdmanualshooterarms = false;

		//Shooter Poker Command
		if(mechanismcontroller->bY ->RE() == true) Commands->cmdmanualshooterpoker = true;
		else Commands->cmdmanualshooterpoker = false;
	}

	else{
		--manualModeDeactivationTimer;

		if(manualModeDeactivationTimer <= 0)
		{
			Commands->cmdisinmechmanual = false;
			//High Shot Intake Command
			if(mechanismcontroller->bRB->State()) Commands->cmdintakehighshot = true;
			else Commands->cmdintakehighshot = false;

			//Low Shot Intake Command
			if(mechanismcontroller->bLB->State()) Commands->cmdintakelowshot = true;
			else Commands->cmdintakelowshot = false;

			//Scale Shot Command
			//if(mechanismcontroller->bX->State() == true) Commands->cmdscaleshot = true;
			//else Commands->cmdscaleshot = false;

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

			//Home arm on the ground
			if(mechanismcontroller->bRS->State()) Commands->cmdresetrobot = true;
			else Commands->cmdresetrobot = false;

			//Arm to carry position
			if(mechanismcontroller->bBack->State()) Commands->cmdarmtocarry = true;
			else Commands->cmdarmtocarry = false;

			//Shot for highest scale
			if(mechanismcontroller->bStart->State()) Commands->cmdscalehighshot = true;
			else Commands->cmdscalehighshot = false;

			//Shot for lowest scale
			if(mechanismcontroller->bX->State()) Commands->cmdscalemidshot = true;
			else Commands->cmdscalemidshot = false;
		} else {
			Commands->cmdmanualshooteranglelower = false;
			Commands->cmdmanualshooterangleraise = false;
		}
	}
}


