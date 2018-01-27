/*
 * DriveManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_DRIVESYSTEM_DRIVEMANAGER_H_
#define SRC_DRIVESYSTEM_DRIVEMANAGER_H_ 1
/* temp includes */
#include <DriveSystem/SwerveLib.h>
#include "ControllerInput/ControllerManager.h"
#include "IO.h"
#include "RobotCommands.h"

	class DriveManager {
	public:
		DriveManager(SwerveLib *swervelib, IO *io, RobotCommands *com, ControllerManager *cntls);

		void ZeroEncoders();

		void CalculateVectors();

		void ApplyIntellegintSwerve();

		void ApplyPIDControl();

	private:
		SwerveLib *_swervelib;
		IO *_io;
		RobotCommands _commands;
		ControllerManager _cntls;
		double _comangle, _commagnitude, _comrotation;
		PIDController *_lfdrvpid, *_rfdrvpid, *_lbdrvpid, *_rbdrvpid;
		PIDController *_lfturnpid, *_rfturnpid, *_lbturnpid, *_rbturnpid;
		double _drvpidi, _drvpidp, _drvpidd, _drvpidf;
		double _turnpidi, _turnpidp, _turnpidd;
		double _pidpollrate;
		double _maxdrivespeed; //Speed is in encoder pulses
		double _currangrf, _curranglf, _curranglb, _currangrb;
		double WhlAngCalcOffset(double, double);
		double _lfwhlangoffset, _rfwhlangoffset, _lbwhlangoffset, _rbwhlangoffset;
	};







#endif /* SRC_DRIVESYSTEM_DRIVEMANAGER_H_ */
