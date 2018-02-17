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
	outputStreamShooter = CameraServer::GetInstance()->PutVideo("ShooterCam", width, height);

	sourceShooter = cv::Mat(width, height, CV_8UC3, cv::Scalar(0,0,0));
	sourceHSV = cv::Mat(width, height, CV_8UC3, cv::Scalar(0,0,0));
	hsvOutput = cv::Mat(width, height, CV_8UC3, cv::Scalar(0,0,0));
	dilateOutput = cv::Mat(width, height, CV_8UC3, cv::Scalar(0,0,0));
	outputShooter = cv::Mat(width, height, CV_8UC1, cv::Scalar(0,0,0));
	contoursOutput = cv::Mat(width, height, CV_8UC1, cv::Scalar(0,0,0));

	finder = ScaleFinder();

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

	while(true) {
		int executionStartTime = frc::GetFPGATime();


		updateCameraSettings();
		cvSinkShooter.GrabFrame(sourceShooter);

		cv::cvtColor(sourceShooter, sourceHSV, cv::COLOR_BGR2HSV);
		cv::inRange(sourceHSV,cv::Scalar(hsvThresholdHue[0], hsvThresholdSaturation[0], hsvThresholdValue[0]), cv::Scalar(hsvThresholdHue[1], hsvThresholdSaturation[1], hsvThresholdValue[1]), hsvOutput);
		cv::dilate(hsvOutput, dilateOutput, cvDilateKernel, cv::Point(-1,-1), cvDilateIterations, cv::BORDER_CONSTANT, cv::Scalar(-1));

		findContoursOutput.clear();
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(dilateOutput, findContoursOutput, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		contoursOutput = cv::Mat(width, height, CV_8UC1, cv::Scalar(0,0,0));


		std::vector<cv::Point> hull;
		filterContoursOutput.clear();
		contourCenters.clear();
		for (std::vector<cv::Point> contour: findContoursOutput) {
			cv::Rect bb = boundingRect(contour);
			if (bb.width < filterContoursMinWidth || bb.width > filterContoursMaxWidth) continue;
			if (bb.height < filterContoursMinHeight || bb.height > filterContoursMaxHeight) continue;
			double area = cv::contourArea(contour);
			if (area < filterContoursMinArea || area > filterContoursMaxArea) continue;
			if (arcLength(contour, true) < filterContoursMinPerimeter) continue;
			cv::convexHull(cv::Mat(contour, true), hull);
			double solid = 100 * area / cv::contourArea(hull);
			if (solid < filterContoursSolidity[0] || solid > filterContoursSolidity[1]) continue;
			if (contour.size() < filterContoursMinVertices || contour.size() > filterContoursMaxVertices)	continue;
			double ratio = (double) bb.width / (double) bb.height;
			if (ratio < filterContoursMinRatio || ratio > filterContoursMaxRatio) continue;
			filterContoursOutput.push_back(contour);
			contourCenters.push_back(cv::Point(bb.x + (double)bb.width / 2, bb.y + (double)bb.height / 2));
		}


		for( int i = 0; i< (int)filterContoursOutput.size(); i++ ){
		   cv::drawContours( contoursOutput, filterContoursOutput, i, cv::Scalar(255,255,255), 1, 8, hierarchy, 0, cv::Point() );
		   cv::circle(contoursOutput, contourCenters[i], 1, cv::Scalar(255,255,255), 1, 8, 0);
		   if(i < ScaleFinder::maxNumPoints){
			   contourCentersForFinder[i][0] = contourCenters[i].x;
			   contourCentersForFinder[i][1] = contourCenters[i].y;
			   std::cout<<"Contour Center: "<<contourCenters[i].x<<", "<<contourCenters[i].y<<"\n";
		   }
		}


		ScaleLine scale = ScaleLine();
		scale = finder.findScale(contourCentersForFinder);
		if(scale.detected){
			cv::line(contoursOutput, cv::Point(scale.startX, scale.startY), cv::Point(scale.endX, scale.endY), cv::Scalar(255,255,255), 1, 8, 0);
		}

		outputStreamShooter.PutFrame(contoursOutput);
		int executionEndTime = frc::GetFPGATime();
		std::cout<<"\n\nExecution time: "<<executionEndTime -executionStartTime<<"\n\n";

	}

}
