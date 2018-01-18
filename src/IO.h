/*
 * IO.h
 *
 *  Created on: Jan 17, 2018
 *      Author: 1800855
 */

#ifndef SRC_IO_H_
#define SRC_IO_H_

#define NUM_ENCODERS 10
#define NUM_SOLENOIDS 10

#include "WPILib.h"
/*
 * Contains an instance of all sensors, motors, and actuators to be passed
 * throughout the entire program
 */
class IO {
public:
	virtual ~IO();

	void g_Initialize();

	IO *GetInstance();

	Encoder GetEncoder(double);

	Compressor GetCompressor();

	Solenoid GetSolenoid(double);

private:
	IO();
	void _InitSensors();
	void _InitMotorControllers();
	void _InitPneumatics();
	static IO *Instance;
	Encoder *encoders [NUM_ENCODERS]; /* we have 10 encoders on the robot */
	Compressor *compressor;
	Solenoid *solenoids[NUM_SOLENOIDS]; /*placeholder 10 */

};

#endif /* SRC_IO_H_ */
