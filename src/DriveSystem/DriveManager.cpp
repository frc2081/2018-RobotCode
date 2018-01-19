/*
 * DriveManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "DriveManager.h"
namespace Drive
{
	DriveManager::DriveManager(SwerveLib *swervelib) {
		_swervelib = swervelib;
		_drivercntl = new cntl(0, 0.05); /* deadband value subject to change */
	}

	void DriveManager::DriveMotors() {
		_drivercntl->UpdateCntl();
		comangle = (atan2(-_drivercntl->LX, _drivercntl->LY) * 180/PI);// + currentFacing;
		commagnitude = sqrt(pow(_drivercntl->LX, 2) + pow(_drivercntl->LY, 2));
		comrotation = _drivercntl->RX;
		_swervelib->CalcWheelVect(commagnitude, comangle, comrotation);
	}
}
