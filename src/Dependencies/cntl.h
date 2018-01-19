/*
 * 	WPILib Controller library
 *
 * 	Organization: FRC2081
 *  Author: Lunar Dust
 *
 *  Do not redistribute this library without the permission of the author.
 */

#ifndef CNTL_H_
#define CNTL_H_

#include "WPILib.h"

//For changing the mapping for different controllers
enum btnNums {
	_bA = 1,
	_bB = 2,
	_bX = 3,
	_bY = 4,
	_bLB = 5,
	_bRB = 6,
	_bBack = 7,
	_bStart = 8,
	_bLS = 9,
	_bRS = 10
};

typedef JoystickButton Btn_t;

class btn
{
	private:
		//JoystickButton object
		Btn_t *_raw;
		bool _State;
		bool _RE;
		bool _Hld;

	public:
		//The current state of the given button
		bool State() const {return this->_State; }
		//True if the current state is true and the last state is false
		bool RE() const {return this->_RE; }
		//The state of the button on the previous loop
		bool Hld() const {return this->_Hld; }

		//Called for all buttons on a controller by calling UpdateCntl()
		void Update();

		//Button constructor
		btn(int, Joystick**);
		virtual ~btn() = default;
};

class cntl
{
	private:
		//Joystick object
		Joystick *_stick;

		double M_deadzone;

	public:
		//Returns controller object, takes controller number and deadzone(0.01 to 1) as argument
		cntl(int, double);

		double LX;
		double LY;
		double RX;
		double RY;
		double RTrig;
		double LTrig;

		//Should be called for each controller at the beginning of each teleop loop
		void UpdateCntl();

		//Button objects of the controller
		btn *bA;
		btn *bB;
		btn *bX;
		btn *bY;
		btn *bLB;
		btn *bRB;
		btn *bBack;
		btn *bStart;
		btn *bLS;
		btn *bRS;
};

#endif /* CNTL_H_ */
