/*
 * ControllerManager.h
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#ifndef SRC_CONTROLLERINPUT_CONTROLLERMANAGER_H_
#define SRC_CONTROLLERINPUT_CONTROLLERMANAGER_H_

#include "cntl.h"


class ControllerManager {
public:
	ControllerManager();

	cntl *drivecontroller;
	cntl *mechanismcontroller;
};

#endif /* SRC_CONTROLLERINPUT_CONTROLLERMANAGER_H_ */
