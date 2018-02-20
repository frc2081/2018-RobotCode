/*
 * VisionManager.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */
#include "VisionManager.h"


	VisionManager::VisionManager() {
		cameraShooter = CameraServer::GetInstance()->StartAutomaticCapture();
		cameraShooter.SetResolution(320, 240);
		cubeCam = CameraServer::GetInstance()->StartAutomaticCapture();
		cubeCam.SetResolution(320, 240);
		cubeCam.SetFPS(30);
	}

