/*
 * RobotCommands.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#include <RobotCommands.h>

RobotCommands::RobotCommands() {

	//TODO:Add all robot Commands here
	cmdramprelease = false;
	cmdscaleshot = false;
	cmdexchangeshot = false;
	cmdswitchshot = false;
	cmdintakehighshot = false;
	cmdintakelowshot = false;
	cmdshiftcube = false;
	cmdrampraiseleft = false;
	cmdrampraiseright = false;
	cmdramplowerleft = false;
	cmdramplowerright = false;
	cmdautopickup = false;
	cmdautoscaleshot = false;
	cmdmanualshooterangleraise = 0;
	cmdmanualshooteranglelower = 0;
	cmdmanualshooterwheelspos = false;
	cmdmanualshooterwheelsneg = false;
	cmdmanualshooterarms = false;
	cmdmanualshooterpoker = false;
	cmdisinmechmanual = false;
	cmdarmtocarry = false;
	cmdscalehighshot = false;
	cmdscalemidshot = false;
	cmdrampopen = false;

	drvmag = 0;
	drvang = 0;
	drvrot = 0;
	cmdresetrobot = false;

}



