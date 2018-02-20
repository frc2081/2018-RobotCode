/*
 * RobotCommands.h
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#ifndef SRC_ROBOTCOMMANDS_H_
#define SRC_ROBOTCOMMANDS_H_

class RobotCommands {
public:
	RobotCommands();

	bool cmdramprelease;
	bool cmdscaleshot;
	bool cmdexchangeshot;
	bool cmdswitchshot;
	bool cmdintakehighshot;
	bool cmdintakelowshot;
	bool cmdshiftcube;
	bool cmdrampraiseleft;
	bool cmdrampraiseright;
	bool cmdramplowerleft;
	bool cmdramplowerright;
	bool cmdautopickup;
	bool cmdautoscaleshot;
	double cmdmanualshooterangleraise;
	double cmdmanualshooteranglelower;
	bool cmdmanualshooterwheelspos;
	bool cmdmanualshooterwheelsneg;
	bool cmdmanualshooterarms;
	bool cmdmanualshooterpoker;
	bool cmdisinmechmanual;
	bool cmdresetrobot;
	bool cmdarmtocarry;
	bool cmdscalehighshot;
	bool cmdscalemidshot;
	bool cmdrampopen;

	double drvang;
	double drvmag;
	double drvrot;
};

#endif /* SRC_ROBOTCOMMANDS_H_ */
