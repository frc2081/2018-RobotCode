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

/*
 * Contains an instance of all sensors, motors, and actuators to be passed
 * throughout the entire program
 */
class IO {
public:

	IO();

	// The scaling to multiply the voltage by to get a meaningful unit 360 degrees / 5 volts = 72
	const int sweerveanglogvoltagetodegrees = 72;
	const double swerveencodercountstodistancecentimeters = .238;
	const double shooterangleencodercountstodegrees = 1;

	enum class CubeIntakeSensor : bool {
		CUBEDETECTED = false,
		NOCUBEDETECTED = true
	};

	VictorSP *drvlbmot;
	VictorSP *drvrbmot;
	VictorSP *drvlfmot;
	VictorSP *drvrfmot;
	WPI_VictorSPX *intakelmot;
	VictorSP *intakermot;
	WPI_VictorSPX *shooterlmot;
	WPI_VictorSPX *shooterrmot;
	TalonSRX *shooteranglmot;
	//TalonSRX *shooterangrmot;
	VictorSP *turnlbmot;
	VictorSP *turnrbmot;
	VictorSP *turnlfmot;
	VictorSP *turnrfmot;
	WPI_VictorSPX * ramprmot;
	WPI_VictorSPX * ramplmot;
	Compressor *compressor;
	Solenoid *solenoidpokeropen;
	Solenoid *solenoidpokerclose;
	Solenoid *shooterarmarticulationopen;
	Solenoid *shooterarmarticulationclose;
	Encoder *encdrvlb;
	Encoder *encdrvlf;
	Encoder *encdrvrb;
	Encoder *encdrvrf;
	AnalogPotentiometer *steerencdrvlb;
	AnalogPotentiometer *steerencdrvlf;
	AnalogPotentiometer *steerencdrvrb;
	AnalogPotentiometer *steerencdrvrf;
	DigitalInput *intakecubesensor;
	DigitalInput *cubechambersensor;
	DigitalInput *swerveresetone;
	DigitalInput *swerveresettwo;
	DigitalInput *armhomeswitch;
	Servo *ramprelease;

	double armP = .7;
	double armI = 0;
	double armD = 0;


private:

};

#endif /* SRC_IO_H_ */
