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
		_drvpidi = 0;
		_drvpidd = 0;
		_drvpidp = 0;
		_turnpidi = 0;
		_turnpidp = 0;
		_turnpidd = 0;
		_pidpollrate = 0.01;
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
		_lfdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidd, lfdrvenc, lfdrv, _pidpollrate);
		_rfdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, rfdrvenc, rfdrv, _pidpollrate);
		_lbdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, lbdrvenc, lbdrv, _pidpollrate);
		_rbdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, rbdrvenc, rbdrv, _pidpollrate);
		_lfturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, lfturnenc, lfturn, _pidpollrate);
		_rfturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, rfturnenc, rfturn, _pidpollrate);
		_rbturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, rbturnenc, rbturn, _pidpollrate);
		_lbturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, lbturnenc, lbturn, _pidpollrate);
		_comangle = 0;
		_commagnitude = 0;
		_comrotation = 0;
		/* temp variables */
		_drivercntl = new cntl(0, 0.05); /* deadband value subject to change */
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

		_lfturnpid->SetSetpoint(_swervelib->whl->angleLF);
		_rfturnpid->SetSetpoint(_swervelib->whl->angleRF);
		_lbturnpid->SetSetpoint(_swervelib->whl->angleLB);
		_rbturnpid->SetSetpoint(_swervelib->whl->angleRB);

	}
}
