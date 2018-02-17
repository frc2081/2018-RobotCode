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

	scaleContourXTable = NetworkTable::GetTable("GRIP/scaleContours");
	scaleContourYTable = NetworkTable::GetTable("GRIP/scaleContours");
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

	std::vector<double> scaleContourX = scaleContourXTable->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> scaleContourY = scaleContourXTable->GetNumberArray("centerY", llvm::ArrayRef<double>());
}
