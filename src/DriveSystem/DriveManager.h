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
#include "Dependencies/Phoenix.h"
namespace Drive {

	class DriveManager {
	public:
		DriveManager(SwerveLib *swervelib);

		void DriveMotors();

	private:
		SwerveLib *_swervelib;
		cntl *_drivercntl;
		double _comangle, _commagnitude, _comrotation;
		PIDController *lfdrvpid, *rfdrvpid, *lbdrvpid, *rbdrvpid;
		PIDController *lfturnpid, *rfturnpid, *rbturnpid, *lbturnpid;
		double drvpidi, drvpidp, drvpidd;
		double turnpidi, turnpidp, turnpidd;
		double pidpollrate;
		/* temp varaibles */
		Encoder lfdrvenc, rfdrvenc, lbdrvenc, rbdrvenc;
		AnalogPotentiometer lfturnenc, rfturnenc, lbturnenc, rbturnenc;
		WPI_VictorSPX lfdrv, rfdrv, lbdrv, rbdrv;
		WPI_TalonSRX lfturn, rfturn, lbturn, rbturn;
	};


}




#endif /* SRC_DRIVESYSTEM_DRIVEMANAGER_H_ */
