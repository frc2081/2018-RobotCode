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
		lfdrvi, lfdrvpid = 0;
		lfdrvp = 0;
		lfdrvd = 0;
		rfdrvi = 0;
		rfdrvp = 0;
		rfdrvd = 0;
		lbdrvi = 0;
		lbdrvp = 0;
		lbdrvd = 0;
		rbdrvi = 0;
		rbdrvp = 0;
		rbdrvd = 0;
		lfturni = 0;
		lfturnp = 0;
		lfturnd = 0;
		rfturni = 0;
		rfturnp = 0;
		rfturnd = 0;
		lbturni = 0;
		lbturnp = 0;
		lbturnd = 0;
		rbturni = 0;
		rbturnp = 0;
		rbturnd = 0;
		pidpollrate = 0.01;
		/* temp */
		lfdrvenc = new Encoder(0);
		rfdrvenc = new Encoder(1);
		lbdrvenc = new Encoder(2);
		rbdrvenc = new Encoder(3);
		lfturnenc = new AnalogPotentiometer(0);
		rfturnenc = new AnalogPotentiometer(1);
		lbturnenc = new AnalogPotentiometer(2);
		rbturnenc = new AnalogPotentiometer(3);
		/* end temp */
		lfdrvpid = new PIDController(lfdrvp, lfdrvi, lfdrvd, lfdrvenc, pidpollrate);
		rfdrvpid = new PIDController(rfdrvp, rfdrvi, rfdrvp, rfdrvenc, pidpollrate);
		lbdrvpid = new PIDController(lbdrvp, lbdrvi, lbdrvp, lbdrvenc, pidpollrate);
		rbdrvpid = new PIDController(rbdrvp, rbdrvi, rbdrvp, rbdrvenc, pidpollrate);
		lfturnpid = new PIDController(lfturnp, lfturni, lfturnp, lfturnenc, pidpollrate);
		rfturnpid = new PIDController(rfturnp, rfturni, rfturnp, rfturnenc, pidpollrate);
		rbturnpid = new PIDController(rbturnp, rbturni, rbturnp, rbturnenc, pidpollrate);
		lbturnpid = new PIDController(lbturnp, lbturni, lbturnp, lbturnenc, pidpollrate);
		/* temp variables */
		lfdrv = new WPI_VictorSPX(0);
		rfdrv = new WPI_VictorSPX(1);
		lbdrv = new WPI_VictorSPX(2);
		rbdrv = new WPI_VictorSPX(3);
	}

	void DriveManager::DriveMotors() {
		_drivercntl->UpdateCntl();
		_comangle = (atan2(-_drivercntl->LX, _drivercntl->LY) * 180/PI);// + currentFacing;
		_commagnitude = sqrt(pow(_drivercntl->LX, 2) + pow(_drivercntl->LY, 2));
		_comrotation = _drivercntl->RX;
		_swervelib->CalcWheelVect(_commagnitude, _comangle, _comrotation);

		lfdrv->Set(_swervelib->whl->speedLF);
	}
}
