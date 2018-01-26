/*
 * IO.h
 *
 *  Created on: Jan 17, 2018
 *      Author: 1800855
 */

#ifndef SRC_IO_H_
#define SRC_IO_H_ 1


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



	/* These make sure the class can't be copied */
	IO(IO const&) = delete;
	void operator=(IO const&) = delete;

	// The scaling to multiply the voltage by to get a meaningful unit 360 degrees / 5 volts = 72
	const int sweerveanglogvoltagetodegrees = 72;

	WPI_VictorSPX *drvlbmot;
	WPI_VictorSPX *drvrbmot;
	WPI_VictorSPX *drvlfmot;
	WPI_VictorSPX *drvrfmot;
	WPI_VictorSPX *intakelmot;
	WPI_VictorSPX *intakermot;
	WPI_VictorSPX *shooterlmot;
	WPI_VictorSPX *shooterrmot;
	TalonSRX *shooteranglmot;
	TalonSRX *shooterangrmot;
	WPI_VictorSPX *turnlbmot;
	WPI_VictorSPX *turnrbmot;
	WPI_VictorSPX *turnlfmot;
	WPI_VictorSPX *turnrfmot;
	Compressor *compressor;
	Solenoid *solenoidrampl;
	Solenoid *solenoidrampr;
	Solenoid *solenoidpoker;
	Solenoid *intakearmarticulation;
	Encoder *encdrvlb;
	Encoder *encdrvlf;
	Encoder *encdrvrb;
	Encoder *encdrvrf;
	AnalogPotentiometer *steerencdrvlb;
	AnalogPotentiometer *steerencdrvlf;
	AnalogPotentiometer *steerencdrvrb;
	AnalogPotentiometer *steerencdrvrf;
	DigitalInput *cubesensor;



	/* put all declarations here */

private:
	IO();

};

#endif /* SRC_IO_H_ */