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
	WPI_VictorSPX *drvrb  = new WPI_VictorSPX(1);
	WPI_VictorSPX *drvlf  = new WPI_VictorSPX(2);
	WPI_VictorSPX *drvrf  = new WPI_VictorSPX(3);
	WPI_VictorSPX *intakel = new WPI_VictorSPX(4);
	WPI_VictorSPX *intaker = new WPI_VictorSPX(5);
	WPI_VictorSPX *shooterl = new WPI_VictorSPX(6);
	WPI_VictorSPX *shooterr = new WPI_VictorSPX(7);
	WPI_VictorSPX *shooterangl = new WPI_VictorSPX(8);
	WPI_VictorSPX *shooterangr = new WPI_VictorSPX(9);
	WPI_VictorSPX *turnlb = new WPI_VictorSPX(10);
	WPI_VictorSPX *turnrb = new WPI_VictorSPX(11);
	WPI_VictorSPX *turnlf = new WPI_VictorSPX(12);
	WPI_VictorSPX *turnrf = new WPI_VictorSPX(13);
	Compressor *compressor = new Compressor();
	Solenoid *solenoidrampl = new Solenoid(0);
	Solenoid *solenoidrampr = new Solenoid(1);


	/* put all declarations here */

private:
	IO() {}
	bool _isinitialized = false;
};

#endif /* SRC_IO_H_ */
