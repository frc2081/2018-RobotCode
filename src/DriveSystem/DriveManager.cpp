/*
* DriveManager.cpp
*
*  Created on: Jan 17, 2018
*      Author: Matthew
*/
#include "DriveManager.h"

DriveManager::DriveManager(IO *io, RobotCommands *com, ControllerManager *cntls) {
	_io = io;
	_commands = com;
	_swervelib = new SwerveLib(27.5, 32);
	_cntls = cntls;
	_drvpidi = 0.0;
	_drvpidd = 0.0;
	_drvpidp = 0.00001;
	_drvpidf = 0.0;
	_turnpidi = 0;
	_turnpidp = -.04;
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
	_maxdrivespeed = 91080; //Speed is in encoder pulses
	_lfdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidd, _drvpidf, io->encdrvlf, io->drvlfmot, _pidpollrate);
	_rfdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, _drvpidf, io->encdrvrf, io->drvrfmot, _pidpollrate);
	_lbdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, _drvpidf, io->encdrvlb, io->drvlbmot, _pidpollrate);
	_rbdrvpid = new PIDController(_drvpidp, _drvpidi, _drvpidp, _drvpidf, io->encdrvrb, io->drvrbmot, _pidpollrate);
	_lfdrvpid->SetContinuous();
	_lfdrvpid->Enable();
	_rfdrvpid->SetContinuous();
	_rfdrvpid->Enable();
	_lbdrvpid->SetContinuous();
	_lbdrvpid->Enable();
	_rbdrvpid->SetContinuous();
	_rbdrvpid->Enable();
	_lfturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, io->steerencdrvlf, io->turnlfmot, _pidpollrate);
	_rfturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, io->steerencdrvrf, io->turnrfmot, _pidpollrate);
	_rbturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, io->steerencdrvrb, io->turnrbmot, _pidpollrate);
	_lbturnpid = new PIDController(_turnpidp, _turnpidi, _turnpidp, io->steerencdrvlb, io->turnlbmot, _pidpollrate);
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
	_prefs = Preferences::GetInstance();
	_lfwhlangoffset = _prefs->GetDouble("LFOffset", 0);
	_rfwhlangoffset = _prefs->GetDouble("RFOffset", 0);
	_lbwhlangoffset = _prefs->GetDouble("LBOffset", 0);
	_rbwhlangoffset = _prefs->GetDouble("RBOffset", 0);
}

void DriveManager::DriveManagerInit() {

}

void DriveManager::DriveManagerPeriodic() {
	_lfturnpid->SetP(_turnpidp);
	_rfturnpid->SetP(_turnpidp);
	_lbturnpid->SetP(_turnpidp);
	_rbturnpid->SetP(_turnpidp);

	_lfturnpid->SetI(_turnpidi);
	_rfturnpid->SetI(_turnpidi);
	_lbturnpid->SetI(_turnpidi);
	_rbturnpid->SetI(_turnpidi);

	_lfturnpid->SetD(_turnpidd);
	_rfturnpid->SetD(_turnpidd);
	_lbturnpid->SetD(_turnpidd);
	_rbturnpid->SetD(_turnpidd);
	CalculateVectors();
	ApplyIntellegintSwerve();
	ApplyPIDControl();

}

void DriveManager::DriveManagerAutoPeriodic() {
	printf("Entering DriveManagerAutoPeriodic\n\n");
	CalculateVectors();
	ApplyIntellegintSwerve();
	AutoApplyPIDControl();
}

void DriveManager::ZeroEncoders() {
	_lfwhlangoffset = _io->steerencdrvlf->Get();
	_rfwhlangoffset = _io->steerencdrvrf->Get();
	_lbwhlangoffset = _io->steerencdrvlb->Get();
	_rbwhlangoffset = _io->steerencdrvrb->Get();
	_prefs->PutDouble("LFOffset", _lfwhlangoffset);
	_prefs->PutDouble("RFOffset", _rfwhlangoffset);
	_prefs->PutDouble("LBOffset", _lbwhlangoffset);
	_prefs->PutDouble("RBOffset", _rbwhlangoffset);

	printf("New LF offset: %.2f", _lfwhlangoffset);
	printf("New RF offset: %.2f", _rfwhlangoffset);
	printf("New LB offset: %.2f", _lbwhlangoffset);
	printf("New RB offset: %.2f", _rbwhlangoffset);
}

double DriveManager::WhlAngCalcOffset(double command, double offset) {
	double target = command + offset;
	if (target > 360) target -= 360;
	return target;
}

void DriveManager::CalculateVectors() {
	_currangrf = _swervelib->whl->angleRF;
	_curranglf = _swervelib->whl->angleLF;
	_currangrb = _swervelib->whl->angleRB;
	_curranglb = _swervelib->whl->angleLB;
	if (_commands->drvmag != 0 || _commands->drvrot != 0) {
		_swervelib->CalcWheelVect(_commands->drvmag, _commands->drvang, _commands->drvrot);
	} else {
		_swervelib->whl->speedLF = 0;
		_swervelib->whl->speedRF = 0;
		_swervelib->whl->speedLB = 0;
		_swervelib->whl->speedRB = 0;


		_swervelib->whl->angleRF = _currangrf;
		_swervelib->whl->angleLF = _curranglf;
		_swervelib->whl->angleRB = _currangrb;
		_swervelib->whl->angleLB = _curranglb;

	}
	//printf("Swerve mag: %.2f  Swerve Ang %.2f\n", _swervelib->whl->speedLF, _swervelib->whl->angleLF);
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

void CheckSetpoint(PIDController *pid, double setpoint, double encoder, double speed) {
	/*
	 * if encoder value within 10 degrees of setpoint &&
	 * if setpoint near 0 -> detect values near 360
	 * set speed setpoint to speed
	 * else speed setpoint to 0
	 */
	if  (encoder < setpoint + 10 && encoder > setpoint - 10) {
		pid->SetSetpoint(speed);
	} else if ((360 - encoder) < setpoint + 10 && (360 - encoder) > setpoint + 10) {
		pid->SetSetpoint(speed);
	} else pid->SetSetpoint(0);
}

void DriveManager::AutoApplyPIDControl() {
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
	_swervelib->whl->speedLF *= _maxdrivespeed;
	_swervelib->whl->speedRF *= _maxdrivespeed;
	_swervelib->whl->speedLB *= _maxdrivespeed;
	_swervelib->whl->speedRB *= _maxdrivespeed;


	//Code to ensure the swerve drive orients it's wheels correctly before attempting to move
	system("clear");
	printf("LF Setpoint: %.2f  RF Setpoint: %.2f  LB Setpoint: %.2f  RB Setpoint: %.2f\n", _lfdrvpid->GetSetpoint(), _rfdrvpid->GetSetpoint(), _lbdrvpid->GetSetpoint(), _rbdrvpid->GetSetpoint());
	printf("LF Encoder: %.2f  RF Encoder: %.2f  LB Encoder: %.2f  RB Encoder: %.2f\n", _io->steerencdrvlf->Get(), _io->steerencdrvrf->Get(), _io->steerencdrvlb->Get(), _io->steerencdrvrb->Get());
	CheckSetpoint(_lfdrvpid, _lfturnpid->GetSetpoint(), _io->steerencdrvlf->Get(), _swervelib->whl->speedLF);
	CheckSetpoint(_rfdrvpid, _rfturnpid->GetSetpoint(), _io->steerencdrvrf->Get(), _swervelib->whl->speedRF);
	CheckSetpoint(_lbdrvpid, _lbturnpid->GetSetpoint(), _io->steerencdrvlb->Get(), _swervelib->whl->speedLB);
	CheckSetpoint(_rbdrvpid, _rbturnpid->GetSetpoint(), _io->steerencdrvrb->Get(), _swervelib->whl->speedRB);
	/*	if ((_io->steerencdrvlf->Get() >= _lfturnpid->GetSetpoint() - 10) && (_io->steerencdrvlf->Get() <= _lfturnpid->GetSetpoint() + 10)
			&& (_io->steerencdrvrb->Get() >= _rbturnpid->GetSetpoint() - 10) && (_io->steerencdrvrb->Get() <= _rbturnpid->GetSetpoint()  + 10)
			&& (_io->steerencdrvlb->Get() >= _lbturnpid->GetSetpoint() - 10) && (_io->steerencdrvlb->Get() <= _lbturnpid->GetSetpoint()  + 10)
			&& (_io->steerencdrvrf->Get() >= _rfturnpid->GetSetpoint() - 10) && (_io->steerencdrvrf->Get() <= _rfturnpid->GetSetpoint()  + 10)) {

				_lfdrvpid->SetSetpoint(_swervelib->whl->speedLF);
				_rfdrvpid->SetSetpoint(_swervelib->whl->speedRF);
				_lbdrvpid->SetSetpoint(_swervelib->whl->speedLB);
				_rbdrvpid->SetSetpoint(_swervelib->whl->speedRB);
			} else {
				printf("Setpoint 0\n");
				_lfdrvpid->SetSetpoint(0);
				_rfdrvpid->SetSetpoint(0);
				_lbdrvpid->SetSetpoint(0);
				_rbdrvpid->SetSetpoint(0);


		}*/
}

void DriveManager::ApplyPIDControl() {

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
	_swervelib->whl->speedLF *= _maxdrivespeed;
	_swervelib->whl->speedRF *= _maxdrivespeed;
	_swervelib->whl->speedLB *= _maxdrivespeed;
	_swervelib->whl->speedRB *= _maxdrivespeed;

	_lfdrvpid->SetSetpoint(_swervelib->whl->speedLF);
	_rfdrvpid->SetSetpoint(_swervelib->whl->speedRF);
	_lbdrvpid->SetSetpoint(_swervelib->whl->speedLB);
	_rbdrvpid->SetSetpoint(_swervelib->whl->speedRB);
}

