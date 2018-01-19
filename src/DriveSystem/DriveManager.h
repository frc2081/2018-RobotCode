/*
 * DriveManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_DRIVESYSTEM_DRIVEMANAGER_H_
#define SRC_DRIVESYSTEM_DRIVEMANAGER_H_ 1
#include <Robot.h>
/* temp includes */
#include "Dependencies/SwerveLib.h"
namespace Drive {

	class DriveManager {
	public:
		DriveManager(SwerveLib *swervelib);

		void DriveMotors();

	private:
		SwerveLib *_swervelib;
		cntl *_drivercntl;
		double comangle, commagnitude, comrotation;
	};


}




#endif /* SRC_DRIVESYSTEM_DRIVEMANAGER_H_ */
