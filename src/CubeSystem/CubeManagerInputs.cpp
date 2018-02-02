/*
 * CubeManagerInputs.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: wentzdr
 */

#include <CubeSystem/CubeManagerInputs.h>

CubeManagerInputs::CubeManagerInputs() {
	intakeCubeSensor = CubeSensor::NO_CUBE_PRESENT;
	shooterCubeSensor = CubeSensor::CUBE_PRESENT;

	shooterangleactualvalue = 0;
}

CubeManagerInputs::~CubeManagerInputs() {
}

CubeManagerInputs::CubeSensor CubeManagerInputs::getIntakeCubeSensor() {

	return intakeCubeSensor;
}

CubeManagerInputs::CubeSensor CubeManagerInputs::getShooterCubeSensor() {

	return shooterCubeSensor;
}

double CubeManagerInputs::getShooterAngleActualValue() {
	return shooterangleactualvalue;
}

void CubeManagerInputs::updateInputs(){
	//TODO: Poll Inputs here
}
