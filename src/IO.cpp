/*
 * IO.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: 1800855
 */

#include "IO.h"

IO::IO() {
	/*
	    LFEncTurn = new AnalogPotentiometer(0, 360, 0);
		RFEncTurn = new AnalogPotentiometer(2, 360, 0);
		LBEncTurn = new AnalogPotentiometer(1, 360, 0);
		RBEncTurn = new AnalogPotentiometer(3, 360, 0);

		LFEncDrv = new Encoder(4, 5, false);
		RFEncDrv = new Encoder(2, 3, false);
		LBEncDrv = new Encoder (6, 7, false);
		RBEncDrv = new Encoder (8, 9, false);
		shooterEnc = new Encoder(0, 1, false);

		//Instantiate the motors based on where they are plugged in
		LFMotTurn = new VictorSP(8);
		RFMotTurn = new VictorSP(12);
		LBMotTurn = new VictorSP(3);
		RBMotTurn = new VictorSP(6);

		LFMotDrv = new VictorSP(9);
		RFMotDrv = new VictorSP(13);
		LBMotDrv = new VictorSP(4);
		RBMotDrv = new VictorSP(7);
	 */
	drvlbmot = new VictorSP(4);//WPI_VictorSPX(15);//
	drvrbmot  = new VictorSP(7);//WPI_VictorSPX(0);//
	drvlfmot  = new VictorSP(9);//WPI_VictorSPX(14);//
	drvrfmot  = new VictorSP(13);//WPI_VictorSPX(1);//
	intakelmot = new WPI_VictorSPX(12);
	intakermot = new WPI_VictorSPX(3);
	shooterlmot = new WPI_VictorSPX(13);
	shooterrmot = new WPI_VictorSPX(2);
	shooteranglmot = new TalonSRX(8);
	shooterangrmot = new TalonSRX(7);
	turnlbmot = new VictorSP(3);//WPI_VictorSPX(10);//
	turnrbmot = new VictorSP(6);//WPI_VictorSPX(5);//
	turnlfmot = new VictorSP(8);//WPI_VictorSPX(9);//
	turnrfmot = new VictorSP(12);//WPI_VictorSPX(6);//
	ramprmot = new WPI_VictorSPX(4);
	ramplmot = new WPI_VictorSPX(11);
	compressor = new Compressor();
	solenoidpoker = new Solenoid(2);
	shooterarmarticulation = new Solenoid(3);
	encdrvlb = new Encoder(6, 7, false);//(0, 1, false, Encoder::EncodingType::k4X);//
	encdrvlf = new Encoder(4, 5, false);//(2, 3, false, Encoder::EncodingType::k4X);//
	encdrvrb = new Encoder(8, 9, false);//(4, 5, false, Encoder::EncodingType::k4X);//
	encdrvrf= new Encoder(2, 3, false);//(6, 7, false, Encoder::EncodingType::k4X);//
	steerencdrvlb = new AnalogPotentiometer(1,360,0);
	steerencdrvlf = new AnalogPotentiometer(0,360,0);
	steerencdrvrb = new AnalogPotentiometer(3,360,0);
	steerencdrvrf = new AnalogPotentiometer(2,360,0);
	intakecubesensor = new DigitalInput(8);
	cubechambersensor = new DigitalInput(9);

	encdrvlb->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvrb->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvlf->SetDistancePerPulse(swerveencodercountstodistancecentimeters);
	encdrvrf->SetDistancePerPulse(swerveencodercountstodistancecentimeters);

	//TODO: Add shooter angle conversion from talon angle to real angle
	//TODO: Add code for determining initial angular position of shooter

}
