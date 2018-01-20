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
#include "Dependencies/cntl.h"
#include "WPILib.h"
#include "IO.h"
namespace Drive {

	class DriveManager {
	public:
		DriveManager(SwerveLib *swervelib, IO *io);

		void CalculateVectors();

		void ApplyIntellegintSwerve();

		void ApplyPIDControl();

	private:
		SwerveLib *_swervelib;
		double _comangle, _commagnitude, _comrotation;
		PIDController *_lfdrvpid, *_rfdrvpid, *_lbdrvpid, *_rbdrvpid;
		PIDController *_lfturnpid, *_rfturnpid, *_rbturnpid, *_lbturnpid;
		double _drvpidi, _drvpidp, _drvpidd;
		double _turnpidi, _turnpidp, _turnpidd;
		double _pidpollrate;
		double _currangrf, _curranglf, _curranglb, _currangrb;
		/* temp varaibles */
		cntl *_drivercntl;
		Encoder *lfdrvenc, *rfdrvenc, *lbdrvenc, *rbdrvenc;
		AnalogPotentiometer *lfturnenc, *rfturnenc, *lbturnenc, *rbturnenc;
		WPI_VictorSPX *lfdrv, *rfdrv, *lbdrv, *rbdrv;
		WPI_VictorSPX *lfturn, *rfturn, *lbturn, *rbturn;
	};


}




#endif /* SRC_DRIVESYSTEM_DRIVEMANAGER_H_ */
