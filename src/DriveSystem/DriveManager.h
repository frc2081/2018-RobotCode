/*
 * DriveManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_DRIVESYSTEM_DRIVEMANAGER_H_
#define SRC_DRIVESYSTEM_DRIVEMANAGER_H_ 1
/* temp includes */
#include "SwerveLib.h"
#include "ctre/Phoenix.h"
#include "cntl.h"
#include <WPILib.h>
#include "IO.h"


	class DriveManager {
	public:
		DriveManager(SwerveLib *swervelib);

		void ZeroEncoders();

		void CalculateVectors();

		void ApplyIntellegintSwerve();

		void ApplyPIDControl();

	private:
		SwerveLib *_swervelib;
		double _comangle, _commagnitude, _comrotation;
		//PIDController *_lfdrvpid, *_rfdrvpid, *_lbdrvpid, *_rbdrvpid;
		PIDController *_lfturnpid, *_rfturnpid, *_lbturnpid, *_rbturnpid;
		//double _drvpidi, _drvpidp, _drvpidd;
		double _turnpidi, _turnpidp, _turnpidd;
		double _pidpollrate;
		double _currangrf, _curranglf, _curranglb, _currangrb;
		double WhlAngCalcOffset(double, double);
		double _lfwhlangoffset, _rfwhlangoffset, _lbwhlangoffset, _rbwhlangoffset;
		/* temp variables */
		cntl *_drivercntl;
		Encoder *lfdrvenc, *rfdrvenc, *lbdrvenc, *rbdrvenc;
		AnalogPotentiometer *lfturnenc, *rfturnenc, *lbturnenc, *rbturnenc;
		//WPI_VictorSPX *_lfdrv, *_rfdrv, *_lbdrv, *_rbdrv;
		//WPI_VictorSPX *_lfturn, *_rfturn, *_lbturn, *_rbturn;

		VictorSP *_lfdrvt, *_rfdrvt, *_lbdrvt, *_rbdrvt;
		VictorSP *_lfturnt, *_rfturnt, *_lbturnt, *_rbturnt;
	};







#endif /* SRC_DRIVESYSTEM_DRIVEMANAGER_H_ */
