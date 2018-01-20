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

#include <WPILib.h>
#include <ctre/Phoenix.h>
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

	/* These make sure the class can't be copied */
	IO(IO const&) = delete;
	void operator=(IO const&) = delete;

	/* put all declarations here */

private:
	IO() {}
};

#endif /* SRC_IO_H_ */
