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
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "ScaleFinder.h"

class VisionManager {
public:
	VisionManager();
	virtual ~VisionManager();


	void visionThread();

private:
	cs::UsbCamera cameraShooter;
	cs::CvSink cvSinkShooter;
	cs::CvSource outputStreamShooter;
	cv::Mat sourceShooter;
	cv::Mat sourceHSV;
	cv::Mat hsvOutput;
	cv::Mat dilateOutput;

	std::vector<std::vector<cv::Point> > findContoursOutput;
	std::vector<std::vector<cv::Point> > filterContoursOutput;
	cv::Mat contoursOutput;
	cv::Mat outputShooter;

	int contourCentersForFinder[ScaleFinder::maxNumPoints][2];
	std::vector<cv::Point> contourCenters;
	ScaleFinder finder;

	int exposure =5;
	int height = 240;
	int width = 320;


	double hsvThresholdHue[2] = {0.0, 180.0};
	double hsvThresholdSaturation[2] = {0.0, 255.0};
	double hsvThresholdValue[2] = {90.80933852161434, 255.0};

	cv::Mat cvDilateKernel;
	int cvDilateIterations = 4.0;  // default Double


	double filterContoursMinArea = 0;  // default Double
	double filterContoursMaxArea = 500;
	double filterContoursMinPerimeter = 0;  // default Double
	double filterContoursMinWidth = 0.0;  // default Double
	double filterContoursMaxWidth = 30.0;  // default Double
	double filterContoursMinHeight = 5.0;  // default Double
	double filterContoursMaxHeight = 30.0;  // default Double
	double filterContoursSolidity[2] = {0, 100};
	double filterContoursMaxVertices = 1000000;  // default Double
	double filterContoursMinVertices = 0.0;  // default Double
	double filterContoursMinRatio = 0.0;  // default Double
	double filterContoursMaxRatio = 4.0;  // default Double
	void updateCameraSettings();



};

#endif /* SRC_VISIONSYSTEM_VISIONMANAGER_H_ */
