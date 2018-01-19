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

	Encoder GetEncoder(double);

	Compressor GetCompressor();

	Solenoid GetSolenoid(double);

	WPI_TalonSRX GetTalon(double);

	WPI_VictorSPX GetVictor(double);

private:
	IO();
	void _InitSensors();
	void _InitMotorControllers();
	void _InitPneumatics();
	static IO *_instance;
	Encoder *_encoders [NUM_ENCODERS];
	Compressor *_compressor;
	Solenoid *_solenoids[NUM_SOLENOIDS];
	WPI_TalonSRX *_talons [NUM_TALONS];
	WPI_VictorSPX *_victors[NUM_VICTORS];


};

#endif /* SRC_IO_H_ */
