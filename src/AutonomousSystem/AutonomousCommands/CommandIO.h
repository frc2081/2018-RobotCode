/*
 * CommandIO.h
 *
 *  Created on: Jan 30, 2017
 *      Author: FIRSTUser
 */

#ifndef SRC_AUTOCOMMANDS_COMMANDIO_H_
#define SRC_AUTOCOMMANDS_COMMANDIO_H_

	struct commandOutput {
		double autoAng;
		double autoSpeed;
		double autoRot;
		bool takeScaleShot;
		bool takeSwitchShot;

		commandOutput() {
			autoAng = 0;
			autoSpeed = 0;
			autoRot = 0;
			takeScaleShot = false;
			takeSwitchShot = false;
		}

		commandOutput(double mag, double ang, double rot) {
			autoAng = ang;
			autoSpeed = mag;
			autoRot = rot;
			takeScaleShot = false;
			takeSwitchShot = false;
		}

		commandOutput(bool scaleShot, bool switchShot) {
			autoAng = 0;
			autoSpeed = 0;
			autoRot = 0;
			takeScaleShot = scaleShot;
			takeSwitchShot = switchShot;
		}
	};

	struct  commandInput {
		double currentGyroReading;
		double LFWhlTurnEnc;
		double RFWhlTurnEnc;
		double RBWhlTurnEnc;
		double LBWhlTurnEnc;
		double LFWhlDrvEnc;
		double RFWhlDrvEnc;
		double RBWhlDrvEnc;
		double LBWhlDrvEnc;
		double shooterEnc;
	};

	enum robotTeam {
		NONE,
		BLUE,
		RED
	};

	enum robotStation {
		UNKNOWN,
		ONE,
		TWO,
		THREE
	};

	enum robotAction {
		NO_AUTO,
		SCALE_SHOT,
		SWITCH_SHOT,
		DRIVE_FORWARD
	};


#endif /* SRC_AUTOCOMMANDS_COMMANDIO_H_ */
