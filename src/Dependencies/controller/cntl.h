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

/**********Configuration**********/

//For changing the mapping for different controllers
enum BTNNUMS {
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

//For adjusting joystick limits (done in percents)
enum STICKLIMITS  {
	kLX = 100,
	kLY = 100,
	kRX = 100,
	kRY = 100
};
/********End Configuration********/

typedef JoystickButton Btn_t;

class btn
{
	private:
		// JoystickButton object
		Btn_t *_raw;
		bool _state;
		bool _re;
		bool _held;

	public:
		// The current state of the given button
		bool State() const {return this->_state; }
		// True if the current state is true and the last state is false
		// This is useful if you want to get a single button input
		bool RE() const {return this->_re; }
		// The state of the button on the previous loop
		bool Held() const {return this->_held; }

		// Called for all buttons on a controller by calling UpdateCntl()
		void Update();

		// Button constructor
		btn(int, Joystick**);
		virtual ~btn() = default;
};

class cntl
{
	private:
		// Joystick object
		Joystick *_stick;

		// Stores the cntl instance's deadband value
		double _deadzone;

	public:
		/**
		 * Creates a new controller instance.
		 *
		 * @param controllerNumber the number of the desired controller (index starts from 0).
		 * @param deadzone the deadzone range desired (0.01 to 1.0).
		 * @return the controller object
		 */
		cntl(int controllernumber, double deadzone);

		double LX;
		double LY;
		double RX;
		double RY;
		double RTrig;
		double LTrig;

		/**
		 * Updates all button values. Should be called at the beginning of each teleop loop
		 */
		void UpdateCntl();

		// Button objects of the controller
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
