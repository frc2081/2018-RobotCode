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
#include <ControllerInput/cntl.h>
class TalonConfiguration {
public:
	TalonConfiguration(IO *io);
	virtual ~TalonConfiguration();

	void TalonConfigInit();
private:
	IO *_io;
	bool _invert; /* pick this based on your preference on what positive motor output should spin to */
	bool _sensorphase; /* pick this so self-test stops reporting sensor-out-of-phase */
	double _exchangeheight, _switchheight, _scaleheight;
	double _maxtalonvolts, _ramptimeout;
};

#endif /* SRC_CUBESYSTEM_TALONCONFIGURATION_H_ */
