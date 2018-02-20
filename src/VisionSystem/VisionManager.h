/*
 * VisionManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_VISIONSYSTEM_VISIONMANAGER_H_
#define SRC_VISIONSYSTEM_VISIONMANAGER_H_

#include "WPILib.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

namespace Vision {

	class VisionManager {
	public:
		VisionManager();
		cs::UsbCamera cameraShooter;
		cs::UsbCamera cubeCam;

	};
}




#endif /* SRC_VISIONSYSTEM_VISIONMANAGER_H_ */
