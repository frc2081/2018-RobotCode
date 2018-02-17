/*
 * ScaleFinder.h
 *
 *  Created on: Feb 14, 2018
 *      Author: wentzdr
 */

#ifndef SRC_SCALEFINDER_H_
#define SRC_SCALEFINDER_H_

#include <iostream>
#include <cmath>
#include "ScaleLine.h"

class ScaleFinder {


public:
	ScaleFinder();
	virtual ~ScaleFinder();

	//Max number of points that ScaleFinder will search through to find a line
	//Useful to limit the max amount of time the algorithm can take to complete
	//Set it in the ScaleLine class
	static const int maxNumPoints = ScaleLine::maxNumPoints;

	// algorithm that performs the search
	//the points array
	ScaleLine findScale(int points[maxNumPoints][2]);

private:
	void updateCals();

	//Cals for what is detected as a scale edge
	int maxDistanceFromLine; //Max allowed distance from a line for a point to be considered "on" the line
	int maxSlope; //Max allowed slope of a line
	int minSlope; //Min allowed slope of a line
	int numReqPoints; //Required number of points for a line to be a scale edge
	int maxAvgSeparation; //Max distance between any two neighboring points on the line

	//Toggle for debug info.
	//Yes, I know I should have used the preprocessor. Shut up.
	bool verbose;

	ScaleLine Line();
};

#endif /* SRC_SCALEFINDER_H_ */
