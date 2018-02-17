/*
 * CubeManagerInputs.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: wentzdr
 */

#include <CubeSystem/CubeManagerInputs.h>

CubeManagerInputs::CubeManagerInputs() {
	intakeCubeSensor = CubeSensor::NO_CUBE_PRESENT;
	shooterCubeSensor = CubeSensor::NO_CUBE_PRESENT;

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

void CubeManagerInputs::updateInputs(IO *Inputs){
	if(Inputs->intakecubesensor->Get()) intakeCubeSensor = CubeSensor::NO_CUBE_PRESENT;
	else intakeCubeSensor = CubeSensor::CUBE_PRESENT;
	if(Inputs->cubechambersensor->Get()) shooterCubeSensor = CubeSensor::NO_CUBE_PRESENT;
	else shooterCubeSensor = CubeSensor::CUBE_PRESENT;
}
