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
		drvpidi = 0;
		drvpidd = 0;
		drvpidp = 0;
		turnpidi = 0;
		turnpidp = 0;
		turnpidd = 0;
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
		lfdrvpid = new PIDController(drvpidp, drvpidi, drvpidd, lfdrvenc, lfdrv, pidpollrate);
		rfdrvpid = new PIDController(drvpidp, drvpidi, drvpidp, rfdrvenc, rfdrv, pidpollrate);
		lbdrvpid = new PIDController(drvpidp, drvpidi, drvpidp, lbdrvenc, lbdrv, pidpollrate);
		rbdrvpid = new PIDController(drvpidp, drvpidi, drvpidp, rbdrvenc, rbdrv, pidpollrate);
		lfturnpid = new PIDController(turnpidp, turnpidi, turnpidp, lfturnenc, lfturn, pidpollrate);
		rfturnpid = new PIDController(turnpidp, turnpidi, turnpidp, rfturnenc, rfturn, pidpollrate);
		rbturnpid = new PIDController(turnpidp, turnpidi, turnpidp, rbturnenc, rbturn, pidpollrate);
		lbturnpid = new PIDController(turnpidp, turnpidi, turnpidp, lbturnenc, lbturn, pidpollrate);
		_comangle = 0;
		_commagnitude = 0;
		_comrotation = 0;
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

		lfdrv.Set(_swervelib->whl->speedLF);
		rfdrv.Set(_swervelib->whl->speedRF);
		rbdrv.Set(_swervelib->whl->speedRB);
		lbdrv.Set(_swervelib->whl->speedLB);

		lfturnpid->SetSetpoint(_swervelib->whl->angleLF);
		rfturnpid->SetSetpoint(_swervelib->whl->angleRF);
		lbturnpid->SetSetpoint(_swervelib->whl->angleLB);
		rbturnpid->SetSetpoint(_swervelib->whl->angleRB);

	}
}
