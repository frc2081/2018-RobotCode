/*
 * VisionManager.cpp
 *
 *  Created on: Feb 13, 2018
 *      Author: blzzrd
 */

#include <VisionSystem/VisionManager.h>

VisionManager::VisionManager() {
	cameraShooter = CameraServer::GetInstance()->StartAutomaticCapture();
	cameraShooter.SetResolution(width, height);
	cameraShooter.SetExposureManual(exposure);
	frc::SmartDashboard::PutNumber("Exposure", exposure);

	cvSinkShooter = CameraServer::GetInstance()->GetVideo();
	outputStreamShooter = CameraServer::GetInstance()->PutVideo("Gray", width, height);

}

VisionManager::~VisionManager() {}

void VisionManager::updateCameraSettings()
{
	int dashboardExposure = frc::SmartDashboard::GetNumber("Exposure", exposure);
	if( dashboardExposure != exposure) {
		exposure = dashboardExposure;
		cameraShooter.SetExposureManual(exposure);
	}
}

void VisionManager::visionThread()
{
	updateCameraSettings();

}
