/*
 * VisionManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "VisionManager.h"
namespace Vision
{
	VisionManager::VisionManager() {
		cameraShooter = CameraServer::GetInstance()->StartAutomaticCapture();
		cameraShooter.SetResolution(320, 240);
		cubeCam = CameraServer::GetInstance()->StartAutomaticCapture();
		cubeCam.SetResolution(320, 240);
	}
}
