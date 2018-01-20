/*
* DriveManager.cpp
*
*  Created on: Jan 17, 2018
*      Author: Matthew
*/
#include "DriveManager.h"

DriveManager::DriveManager(SwerveLib *swervelib, IO *io) {
	_swervelib = swervelib;
	_drvpidi = 0;
	_drvpidd = 0;
	_drvpidp = 0;
	_turnpidi = 0;
	_turnpidp = 0;
	_turnpidd = 0;
	_pidpollrate = 0.01;
	_currangrf = 0;
	_curranglf = 0;
	_curranglb = 0;
	_currangrb = 0;
	/* temp */
	lfdrvenc = new Encoder(0, 1, false);
	rfdrvenc = new Encoder(2, 3, false);
	lbdrvenc = new Encoder(4, 5, false);
	rbdrvenc = new Encoder(6, 7, false);
	lfturnenc = new AnalogPotentiometer(0);
	rfturnenc = new AnalogPotentiometer(1);
	lbturnenc = new AnalogPotentiometer(2);
	rbturnenc = new AnalogPotentiometer(3);
	_drivercntl = new cntl(0, 0.05); /* deadband value subject to change */
	/*
	_lfdrv = new WPI_VictorSPX(0);
	_rfdrv = new WPI_VictorSPX(1);
	_lbdrv = new WPI_VictorSPX(2);
	_rbdrv = new WPI_VictorSPX(3);
	_lbturn = new WPI_VictorSPX(4);
	_lfturn = new WPI_VictorSPX(5);
	_rfturn = new WPI_VictorSPX(6);
	_lbturn = new WPI_VictorSPX(7);
	*/
	/* end temp */
	_lfdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidd, lfdrvenc, _lfdrv, _pidpollrate);
	_rfdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, rfdrvenc, _rfdrv, _pidpollrate);
	_lbdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, lbdrvenc, _lbdrv, _pidpollrate);
	_rbdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, rbdrvenc, _rbdrv, _pidpollrate);
	_lfturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, lfturnenc, _lfturn, _pidpollrate);
	_rfturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, rfturnenc, _rfturn, _pidpollrate);
	_rbturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, rbturnenc, _rbturn, _pidpollrate);
	_lbturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, lbturnenc, _lbturn, _pidpollrate);
	_comangle = 0;
	_commagnitude = 0;
	_comrotation = 0;
}

void DriveManager::CalculateVectors() {
	_drivercntl->UpdateCntl();
	_comangle = (atan2(-_drivercntl->LX, _drivercntl->LY) * 180/PI);
	_commagnitude = sqrt(pow(_drivercntl->LX, 2) + pow(_drivercntl->LY, 2));
	_comrotation = _drivercntl->RX;
	_swervelib->CalcWheelVect(_commagnitude, _comangle, _comrotation);
}

void DriveManager::ApplyIntellegintSwerve() {
	if (fabs(_swervelib->whl->angleRF - _currangrf) > 90 &&
			(_swervelib->whl->angleRF - _currangrf < 270)) {
		_swervelib->whl->angleRF = ((int)_swervelib->whl->angleRF + 180) % 360;
		_swervelib->whl->speedRF *= -1;
	}
	if (fabs(_swervelib->whl->angleLF - _curranglf) > 90 &&
			(_swervelib->whl->angleLF - _curranglf < 270)) {
		_swervelib->whl->angleLF = ((int)_swervelib->whl->angleLF + 180) % 360;
		_swervelib->whl->speedLF *= -1;
	}
	if (fabs(_swervelib->whl->angleRB - _currangrb) > 90 &&
			(_swervelib->whl->angleRB - _currangrb < 270)) {
		_swervelib->whl->angleRB = ((int)_swervelib->whl->angleRB + 180) % 360;
		_swervelib->whl->speedRB *= -1;
	}
	if (fabs(_swervelib->whl->angleLB - _curranglb) > 90 &&
			(_swervelib->whl->angleLB - _curranglb < 270)) {
		_swervelib->whl->angleLB = ((int)_swervelib->whl->angleLB + 180) % 360;
		_swervelib->whl->speedLB *= -1;
	}
}

void DriveManager::ApplyPIDControl() {

	/* Not PID for testing purposes */
	_lfdrv->Set(_swervelib->whl->speedLF);
	_rfdrv->Set(_swervelib->whl->speedRF);
	_rbdrv->Set(_swervelib->whl->speedRB);
	_lbdrv->Set(_swervelib->whl->speedLB);

	_lfturnpid->SetSetpoint(_swervelib->whl->angleLF);
	_rfturnpid->SetSetpoint(_swervelib->whl->angleRF);
	_lbturnpid->SetSetpoint(_swervelib->whl->angleLB);
	_rbturnpid->SetSetpoint(_swervelib->whl->angleRB);


	/* will add speed pid control for the wheels later, after encoder pulses are measured */
	//_lfdrvpid->SetSetpoint(0);

	}

