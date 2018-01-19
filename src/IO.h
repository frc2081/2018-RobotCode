/*
 * IO.h
 *
 *  Created on: Jan 17, 2018
 *      Author: 1800855
 */

#ifndef SRC_IO_H_
#define SRC_IO_H_

#define NUM_ENCODERS 10 /* we have 10 encoders on the robot */
#define NUM_SOLENOIDS 10 /*placeholder 10 */
#define NUM_TALONS 4 /* we only use talons to control steering for the swerve drive */
#define NUM_VICTORS 8 /* we use victorSPX's everywhere else */

#include "WPILib.h"
#include <Dependencies/Phoenix.h>
/*
 * Contains an instance of all sensors, motors, and actuators to be passed
 * throughout the entire program
 */
class IO {
public:
	virtual ~IO();

	void Initialize();

	IO *GetInstance();
	WPI_VictorSPX *drvlb;
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
	WPI_TalonSRX *turnlb;
	WPI_TalonSRX *turnlrb;
	WPI_TalonSRX *turnlf;
	WPI_TalonSRX *turnrf;
	WPI_TalonSRX *turnlb;
	/* put all declarations here */

private:
	IO();
	static IO *_instance;


};

#endif /* SRC_IO_H_ */
