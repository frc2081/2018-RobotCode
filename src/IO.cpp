/*
 * IO.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: 1800855
 */

#include "IO.h"

IO::IO() {

	drvlbmot = new WPI_VictorSPX(0);
	drvrbmot  = new WPI_VictorSPX(1);
	drvlfmot  = new WPI_VictorSPX(2);
	drvrfmot  = new WPI_VictorSPX(3);
	intakelmot = new WPI_VictorSPX(4);
	intakermot = new WPI_VictorSPX(5);
	shooterlmot = new WPI_VictorSPX(6);
	shooterrmot = new WPI_VictorSPX(7);
	shooteranglmot = new TalonSRX(8);
	shooterangrmot = new TalonSRX(9);
	turnlbmot = new WPI_VictorSPX(10);
	turnrbmot = new WPI_VictorSPX(11);
	turnlfmot = new WPI_VictorSPX(12);
	turnrfmot = new WPI_VictorSPX(13);
	compressor = new Compressor();
	solenoidpoker = new Solenoid(2);
	shooterarmarticulation = new Solenoid(3);
	encdrvlb = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	encdrvlf = new Encoder(2, 3, false, Encoder::EncodingType::k4X);
	encdrvrb = new Encoder(4, 5, false, Encoder::EncodingType::k4X);
	encdrvrf= new Encoder(6, 7, false, Encoder::EncodingType::k4X);
	steerencdrvlb = new AnalogPotentiometer(0,sweerveanglogvoltagetodegrees,0);
	steerencdrvlf = new AnalogPotentiometer(1,sweerveanglogvoltagetodegrees,0);
	steerencdrvrb = new AnalogPotentiometer(2,sweerveanglogvoltagetodegrees,0);
	steerencdrvrf = new AnalogPotentiometer(3,sweerveanglogvoltagetodegrees,0);
	intakecubesensor = new DigitalInput(8);
	cubechambersensor = new DigitalInput(9);

	encdrvlb->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvrb->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvlf->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvrf->SetDistancePerPulse(swerveencodercountstodistancecentimeters);

	//TODO: Add shooter angle conversion from talon angle to real angle
	//TODO: Add code for determining initial angular position of shooter

}
