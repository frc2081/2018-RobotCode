/*
 * TalonConfiguration.h
 *
 *  Created on: Jan 26, 2018
 *      Author: support
 */

#ifndef SRC_CUBESYSTEM_TALONCONFIGURATION_H_
#define SRC_CUBESYSTEM_TALONCONFIGURATION_H_
#include "IO.h"
#include "RobotCommands.h"
#include "CubeManagerIO.h"

//temp
#include "cntl.h"
class TalonConfiguration {
public:
	TalonConfiguration(IO *io);
	virtual ~TalonConfiguration();

	void TalonConfigInit();

	void TalonConfigPeriodic(RobotCommands *commands);//, CubeManagerIO *cubeio);

private:
	IO *_io;
	cntl *_cntl1;
	bool _invert; /* pick this based on your preference on what positive motor output should spin to */
	bool _sensorphase; /* pick this so self-test stops reporting sensor-out-of-phase */
	double _exchangeheight, _switchheight, _scaleheight;
};

#endif /* SRC_CUBESYSTEM_TALONCONFIGURATION_H_ */
