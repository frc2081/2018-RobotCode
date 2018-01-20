/*
 * IO.h
 *
 *  Created on: Jan 17, 2018
 *      Author: 1800855
 */

#ifndef SRC_IO_H_
#define SRC_IO_H_ 1

#define NUM_ENCODERS 10 /* we have 10 encoders on the robot */
#define NUM_SOLENOIDS 10 /*placeholder 10 */
#define NUM_TALONS 4 /* we only use talons to control steering for the swerve drive */
#define NUM_VICTORS 8 /* we use victorSPX's everywhere else */

#include <WPILib.h>
#include "ctre/Phoenix.h"
//#include "ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h"
/*
 * Contains an instance of all sensors, motors, and actuators to be passed
 * throughout the entire program
 */
class IO {
public:
	static IO& GetInstance()
	{
		static IO instance;
		return instance;
	}

	void Initialize();

	/* These make sure the class can't be copied */
	IO(IO const&) = delete;
	void operator=(IO const&) = delete;


	WPI_VictorSPX *drvlb = new WPI_VictorSPX(0);
	WPI_VictorSPX *drvrb;
	WPI_VictorSPX *drvlf;
	WPI_VictorSPX *drvrf;
	WPI_VictorSPX *intakel;
	WPI_VictorSPX *intaker;
	WPI_VictorSPX *shooterl;
	WPI_VictorSPX *shooterr;
	WPI_VictorSPX *shooterangl;
	WPI_VictorSPX *shooterangr;
	Compressor *compressor;
	Solenoid *solenoidrampl;
	Solenoid *solenoidrampr;
	WPI_VictorSPX *turnlb;
	WPI_VictorSPX *turnrb;
	WPI_VictorSPX *turnlf;
	WPI_VictorSPX *turnrf;
	/* put all declarations here */

private:
	IO() {}
	bool _isinitialized = false;
};

#endif /* SRC_IO_H_ */
