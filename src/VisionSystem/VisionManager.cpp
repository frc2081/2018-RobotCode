/*
 * VisionManager.cpp
 *
 *  Created on: Feb 13, 2018
 *      Author: blzzrd
 */

#include <VisionSystem/VisionManager.h>

VisionManager::VisionManager() {
	camera = CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(width, height);
	camera.SetExposureManual(exposure);
	frc::SmartDashboard::PutNumber("Exposure", exposure);
}

VisionManager::~VisionManager() {}

void VisionManager::updateCameraSettings()
{
	int dashboardExposure = frc::SmartDashboard::GetNumber("Exposure", 20);
	if( dashboardExposure != exposure) {
		exposure = dashboardExposure;
		camera.SetExposureManual(exposure);
	}
}

void VisionManager::visionPeriodic()
{
	updateCameraSettings();
}
