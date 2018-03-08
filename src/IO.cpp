/*
 * IO.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: 1800855
 */

#include "IO.h"

IO::IO() {
	drvlbmot = new WPI_VictorSPX(15);
	drvrbmot  = new WPI_VictorSPX(0);
	drvlfmot  = new WPI_VictorSPX(14);
	drvrfmot  = new WPI_VictorSPX(1);
	intakelmot = new WPI_VictorSPX(12);
	intakermot = new VictorSP(9);
	shooterlmot = new WPI_VictorSPX(13);
	shooterrmot = new WPI_VictorSPX(2);
	shooteranglmot = new TalonSRX(8);
	//shooterangrmot = new TalonSRX(7);
	turnlbmot = new WPI_VictorSPX(10);
	turnrbmot = new WPI_VictorSPX(5);
	turnlfmot = new WPI_VictorSPX(9);
	turnrfmot = new WPI_VictorSPX(6);
	ramprmot = new WPI_VictorSPX(4);
	ramplmot = new WPI_VictorSPX(11);
	compressor = new Compressor();
	solenoidpokeropen = new Solenoid(0);
	solenoidpokerclose = new Solenoid(1);
	shooterarmarticulationopen = new Solenoid(2);
	shooterarmarticulationclose = new Solenoid(3);
	encdrvlb = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	encdrvlf = new Encoder(2, 3, false, Encoder::EncodingType::k4X);
	encdrvrb = new Encoder(4, 5, false, Encoder::EncodingType::k4X);
	encdrvrf= new Encoder(6, 7, false, Encoder::EncodingType::k4X);
	steerencdrvlb = new AnalogPotentiometer(0,360,0);
	steerencdrvlf = new AnalogPotentiometer(1,360,0);
	steerencdrvrb = new AnalogPotentiometer(2,360,0);
	steerencdrvrf = new AnalogPotentiometer(3,360,0);
	intakecubesensor = new DigitalInput(8);
	cubechambersensor = new DigitalInput(9);
	swerveresetone = new DigitalInput(10);
	swerveresettwo = new DigitalInput(11);
	armhomeswitch = new DigitalInput(12);
	ramprelease = new Servo(0);
	intakelmot->SetInverted(true);
	intakermot->SetInverted(true);
	shooterlmot->SetInverted(true);
	shooterrmot->SetInverted(true);
	encdrvlb->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvrb->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvlf->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvrf->SetDistancePerPulse(swerveencodercountstodistancecentimeters);

	//turnlbmot->ConfigOpenloopRamp(0, 10);
	//turnrbmot->ConfigOpenloopRamp(0, 10);
	//turnlfmot->ConfigOpenloopRamp(0, 10);
	//turnrfmot->ConfigOpenloopRamp(0, 10);

	//drvlbmot->ConfigOpenloopRamp(.1, 10);
	//drvrbmot->ConfigOpenloopRamp(.1, 10);
	//drvlfmot->ConfigOpenloopRamp(.1, 10);
	//drvrfmot->ConfigOpenloopRamp(.1, 10);
	//TODO: Add shooter angle conversion from talon angle to real angle
	//TODO: Add code for determining initial angular position of shooter

}
