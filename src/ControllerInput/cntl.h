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
enum BTNENUMS {
	kbA = 1,
	kbB = 2,
	kbX = 3,
	kbY = 4,
	kbLB = 5,
	kbRB = 6,
	kbBack = 7,
	kbStart = 8,
	kbLS = 9,
	kbRS = 10
};

enum RANGELIMITS {
	kLX = 100,
	kLY = 100,
	kRX = 100,
	kRY = 100
};

typedef JoystickButton Btn_t;

class btn
{
	private:
		//JoystickButton object
		Btn_t *_raw;
		bool _state;
		bool _re;
		bool _held;

	public:
		//The current state of the given button
		bool State() const {return this->_state; }
		//True if the current state is true and the last state is false
		bool RE() const {return this->_re; }
		//The state of the button on the previous loop
		bool Held() const {return this->_held; }

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

		double _deadzone;
		double _rangelimit;

	public:
		//Returns controller object, takes controller number and deadzone(0.01 to 1) as argument
		cntl(int, double, double);

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
