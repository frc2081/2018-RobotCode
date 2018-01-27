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
#include "CubeManagerIO.h"


class CubeManager
{
public:
	CubeManager();
	void CubeManagerPeriodic(RobotCommands *Commands, IO *RioIO);
	void CubeManagerInit();
	CubeManagerIO *IntakeIO;
	CubeManagerIO *SwitchShotIO;
	CubeManagerIO *ScaleShotIO;
	CubeManagerIO *DeliveryIO;
	CubeManagerIO *DefaultCommands;

private:
	void AssignIO(CubeManagerIO *Commands, IO *RioIO);
};

#endif /* SRC_CUBESYSTEM_CUBEMANAGER_H_ */
