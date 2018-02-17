/*
 * ScaleLine.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: wentzdr
 */

#include "ScaleLine.h"

ScaleLine::ScaleLine() {
	// TODO Auto-generated constructor stub

	startX = 0;
	startY = 0;
	endX = 0;
	endY = 0;
	midX = 0;
	midY = 0;

	numPoints = 0;
	slope = 0;
	offset = 0;

	detected = false;

	avgSeparation = 0;

	for( int i =0; i < maxNumPoints; i++) {
		linePoints[i][0] = 0;
		linePoints[i][1] = 0;
	}

}

ScaleLine::~ScaleLine() {
	// TODO Auto-generated destructor stub
}

