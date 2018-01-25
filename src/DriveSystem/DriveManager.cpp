/*
* DriveManager.cpp
*
*  Created on: Jan 17, 2018
*      Author: Matthew
*/
#include "DriveManager.h"

DriveManager::DriveManager(SwerveLib *swervelib, IO &io) {
	_swervelib = swervelib;
	_drvpidi = 0.0;
	_drvpidd = 0.0;
	_drvpidp = 0.00001;
	_drvpidf = 0.0;
	SmartDashboard::PutNumber("rbp: ", 0);
	SmartDashboard::PutNumber("rbi: ", 0);
	SmartDashboard::PutNumber("rbd: ", 0);
	SmartDashboard::PutNumber("rbf: ", 0);
	_turnpidi = 0;
	_turnpidp = 0.04;
	_turnpidd = 0;
	_pidpollrate = 0.01;
	_currangrf = 0;
	_curranglf = 0;
	_curranglb = 0;
	_currangrb = 0;
	_lfwhlangoffset = 0;
	_rfwhlangoffset = 0;
	_lbwhlangoffset = 0;
	_rbwhlangoffset = 0;
	_maxdrivespeed = 4554; //Speed is in RPM of the CIM motor
	/* temp */
	lfdrvenc = new Encoder(4, 5, false);
	rfdrvenc = new Encoder(2, 3, false);
	lbdrvenc = new Encoder(6, 7, false);
	rbdrvenc = new Encoder(8, 9, false);
	lfturnenc = new AnalogPotentiometer(0, 360, 0);
	rfturnenc = new AnalogPotentiometer(2, 360, 0);
	lbturnenc = new AnalogPotentiometer(1, 360, 0);
	rbturnenc = new AnalogPotentiometer(3, 360, 0);
	_drivercntl = new cntl(0, 0.15); /* deadband value subject to change */
	_lfdrvt = new VictorSP(9);
	_rfdrvt = new VictorSP(13);
	_lbdrvt = new VictorSP(4);
	_rbdrvt = new VictorSP(7);
	_lfturnt = new VictorSP(8);
	_rfturnt = new VictorSP(12);
	_lbturnt = new VictorSP(3);
	_rbturnt = new VictorSP(6);
	/*
	_lfdrv = new WPI_VictorSPX(0);
	_rfdrv = new WPI_VictorSPX(1);
	_lbdrv = new WPI_VictorSPX(2);
	_rbdrv = new WPI_VictorSPX(3);
	_lbturn = new WPI_VictorSPX(4);
	_lfturn = new WPI_VictorSPX(5);
	_rfturn = new WPI_VictorSPX(6);
	_rbturn = new WPI_VictorSPX(7);
	*/
	/* end temp */
	_lfdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidd, _drvpidf, lfdrvenc, _lfdrvt, _pidpollrate);
	_rfdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, _drvpidf, rfdrvenc, _rfdrvt, _pidpollrate);
	_lbdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, _drvpidf, lbdrvenc, _lbdrvt, _pidpollrate);
	_rbdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, _drvpidf, rbdrvenc, _rbdrvt, _pidpollrate);
	_lfdrvpid->SetContinuous();
	_lfdrvpid->Enable();
	_rfdrvpid->SetContinuous();
	_rfdrvpid->Enable();
	_lbdrvpid->SetContinuous();
	_lbdrvpid->Enable();
	_rbdrvpid->SetContinuous();
	_rbdrvpid->Enable();
	_lfturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, lfturnenc, _lfturnt, _pidpollrate);
	_rfturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, rfturnenc, _rfturnt, _pidpollrate);
	_rbturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, rbturnenc, _rbturnt, _pidpollrate);
	_lbturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, lbturnenc, _lbturnt, _pidpollrate);
	_lfturnpid->SetInputRange(0, 360);
	_lfturnpid->SetOutputRange(-1, 1);
	_lfturnpid->SetContinuous();
	_lfturnpid->Enable();
	_rfturnpid->SetInputRange(0, 360);
	_rfturnpid->SetOutputRange(-1, 1);
	_rfturnpid->SetContinuous();
	_rfturnpid->Enable();
	_lbturnpid->SetInputRange(0, 360);
	_lbturnpid->SetOutputRange(-1, 1);
	_lbturnpid->SetContinuous();
	_lbturnpid->Enable();
	_rbturnpid->SetInputRange(0, 360);
	_rbturnpid->SetOutputRange(-1, 1);
	_rbturnpid->SetContinuous();
	_rbturnpid->Enable();
	_comangle = 0;
	_commagnitude = 0;
	_comrotation = 0;
}

void DriveManager::ZeroEncoders() {
	_lfwhlangoffset = lfturnenc->Get();
	_rfwhlangoffset = rfturnenc->Get();
	_lbwhlangoffset = lbturnenc->Get();
	_rbwhlangoffset = rbturnenc->Get();
}

double DriveManager::WhlAngCalcOffset(double command, double offset) {
	double target = command + offset;
	if (target > 360) target -= 360;
	return target;
}

void DriveManager::CalculateVectors() {
	_drivercntl->UpdateCntl();
	_comangle = (atan2(-_drivercntl->LX, _drivercntl->LY) * 180/PI);
	_commagnitude = sqrt(pow(_drivercntl->LX, 2) + pow(_drivercntl->LY, 2));
	_comrotation = _drivercntl->RX;
	_currangrf = _swervelib->whl->angleRF;
	_curranglf = _swervelib->whl->angleLF;
	_currangrb = _swervelib->whl->angleRB;
	_curranglb = _swervelib->whl->angleLB;
	if (_drivercntl->LX != 0 || _drivercntl->LY != 0 || _drivercntl->RX != 0) {
		_swervelib->CalcWheelVect(_commagnitude, _comangle, _comrotation);
	} else {
		_swervelib->whl->speedLF = 0;
		_swervelib->whl->speedRF = 0;
		_swervelib->whl->speedLB = 0;
		_swervelib->whl->speedRB = 0;
	}

	printf("Commanded Angle: %.2f\n", _comangle);
	printf("Commanded Magnitude: %.2f\n", _commagnitude);
	printf("Commanded Rotation: %.2f\n", _comrotation);
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

	/*printf("Right Front Angle: %.2f\n", _swervelib->whl->angleRF);
	printf("Left Front Angle: %.2f\n", _swervelib->whl->angleLF);
	printf("Right Back Angle: %.2f\n", _swervelib->whl->angleRB);
	printf("Left Back Angle: %.2f\n", _swervelib->whl->angleLB);*/
}

void DriveManager::ApplyPIDControl() {

	/* Not PID for testing purposes */
	//_lfdrvt->Set(_swervelib->whl->speedLF);
	//_rfdrvt->Set(_swervelib->whl->speedRF);
	//_rbdrvt->Set(_swervelib->whl->speedRB);
	//_lbdrvt->Set(_swervelib->whl->speedLB);
	double rbp = SmartDashboard::GetNumber("rbp: ", 0);
	double rbi = SmartDashboard::GetNumber("rbi: ", 0);
	double rbd = SmartDashboard::GetNumber("rbd: ", 0);
	double rbf = SmartDashboard::GetNumber("rbf: ", 0);

	_lfturnpid->SetSetpoint(WhlAngCalcOffset(_swervelib->whl->angleLF, _lfwhlangoffset));
	_rfturnpid->SetSetpoint(WhlAngCalcOffset(_swervelib->whl->angleRF, _rfwhlangoffset));
	_lbturnpid->SetSetpoint(WhlAngCalcOffset(_swervelib->whl->angleLB, _lbwhlangoffset));
	_rbturnpid->SetSetpoint(WhlAngCalcOffset(_swervelib->whl->angleRB, _rbwhlangoffset));

	/*
	 * 138 pulses/rotation of wheel
	 * 20 pulses/rotation of cim
	 * 6.9 cim rotations/1 wheel rotation
	 * max speed - 11.5 ft/s -> 3.5052 m/s || 660 RPM of wheel
	 * 4554 RPM on cim - max
	 */
	if ((int)lfturnenc->Get() >= (int)_lfturnpid->GetSetpoint() - 1 || (int)lfturnenc->Get() <= (int)_lfturnpid->GetSetpoint() + 1) {
		if((int)rfturnenc->Get() >= (int)_rfturnpid->GetSetpoint() - 1) {
		_swervelib->whl->speedLF *= _maxdrivespeed * 20;
		_swervelib->whl->speedRF *= _maxdrivespeed * 20;
		_swervelib->whl->speedLB *= _maxdrivespeed * 20;
		_swervelib->whl->speedRB *= _maxdrivespeed * 20;
		_lfdrvpid->SetSetpoint(_swervelib->whl->speedLF);
		_rfdrvpid->SetSetpoint(_swervelib->whl->speedRF);
		_lbdrvpid->SetSetpoint(_swervelib->whl->speedLB);
		_rbdrvpid->SetSetpoint(_swervelib->whl->speedRB);
		}
	}

	printf("Right Back Speed Set To: %.2f\n", _rbdrvpid->Get());

	printf("Right Back Angle: %.2f\n", _rbturnpid->Get());

	}

