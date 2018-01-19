/*
 *  cntl.cpp
 *
 *  Created on: Oct 6, 2016
 *      Author: Lunar Dust
 */
#include <cntl.h>

btn::btn(int button, frc::Joystick **s) {
	_raw = new Btn_t(*s, button);
	_Hld = false;
	_State = false;
	_RE = false;
}

void btn::Update() {
	_Hld = _State;
	_State = _raw->Grab();
	_RE = false;
	if(_Hld != _State && !_Hld) {
		_RE = true;
	}
}

cntl::cntl(int port, double deadzone) {
	_stick = new frc::Joystick(port);
	RX = 0.0;
	RY = 0.0;
	LX = 0.0;
	LY = 0.0;
	RTrig = 0.0;
	LTrig = 0.0;

	M_deadzone = deadzone;

	bA = new btn(_bA, &_stick);
	bB = new btn(_bB, &_stick);
	bX = new btn(_bX, &_stick);
	bY = new btn(_bY, &_stick);
	bLB = new btn(_bLB, &_stick);
	bRB = new btn(_bRB, &_stick);
	bBack = new btn(_bBack, &_stick);
	bStart = new btn(_bStart, &_stick);
	bLS = new btn(_bLS, &_stick);
	bRS = new btn(_bRS, &_stick);
}

const double applyDeadzone(double input, double zone) {
	double o = fabs(input) - zone;
	o /= (1 - zone);
	if(o < 0) {
		o = 0;
	}
	if(input < 0) {
		o *= -1;
	}
	if((o + 0.0) == 0.0) {
		o = 0.0;
	}
	return o;
}

void cntl::UpdateCntl() {
	LX = applyDeadzone(_stick->GetX(), M_deadzone);
	LY = applyDeadzone(_stick->GetY(), M_deadzone);
	RX = applyDeadzone(_stick->GetRawAxis(4), M_deadzone);
	RY = applyDeadzone(_stick->GetRawAxis(5), M_deadzone);

	//Commented for testing
	//RTrig = applyDeadzone(_stick->GetRawAxis(3), M_deadzone);
	//LTrig = applyDeadzone(_stick->GetRawAxis(2), M_deadzone);
	RY *= -1;
	LY *= -1;

	bA->Update();
	bB->Update();
	bX->Update();
	bY->Update();
	bLB->Update();
	bRB->Update();
	bBack->Update();
	bStart->Update();
	bLS->Update();
	bRS->Update();
}
