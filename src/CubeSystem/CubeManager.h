/*
 * CubeManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_CUBESYSTEM_CUBEMANAGER_H_
#define SRC_CUBESYSTEM_CUBEMANAGER_H_ 1

#include "ControllerInput/ControllerManager.h"
#include "RobotCommands.h"
#include "IO.h"


class CubeManager
{
public:
	CubeManager();
	void CubeManagerPeriodic(RobotCommands *Commands, IO *RioIO);
	void CubeManagerInit();

private:
};

#endif /* SRC_CUBESYSTEM_CUBEMANAGER_H_ */
