/*
 * VisionManager.h
 *
 *  Created on: Feb 13, 2018
 *      Author: blzzrd
 */

#ifndef SRC_VISIONSYSTEM_VISIONMANAGER_H_
#define SRC_VISIONSYSTEM_VISIONMANAGER_H_

#include "WPILib.h"
#include <SmartDashboard/SmartDashboard.h>

class VisionManager {
public:
	VisionManager();
	virtual ~VisionManager();


	void visionPeriodic();

private:
	cs::UsbCamera camera;

	int exposure =5;
	int height = 240;
	int width = 320;

	void updateCameraSettings();



};

#endif /* SRC_VISIONSYSTEM_VISIONMANAGER_H_ */
