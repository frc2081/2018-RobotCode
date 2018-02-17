/*
 * ScaleLine.h
 *
 *  Created on: Feb 15, 2018
 *      Author: wentzdr
 */

#ifndef SRC_SCALELINE_H_
#define SRC_SCALELINE_H_

class ScaleLine {
public:
	ScaleLine();
	virtual ~ScaleLine();

	//Key points on a line that represents a scale edge
	int startX;
	int startY;
	int endX;
	int endY;
	int midX;
	int midY;

	//Average separation between points on the line
	double avgSeparation;

	//Line data
	int numPoints;
	double slope;
	int offset;

	//Set to true if this object contains a scale edge line
	//If false, no scale edge was detected
	bool detected;

	//Max number of points that a scale edge line can contain
	//Also sets the max number of points that ScaleFinder will search
	//Useful for limiting the total amount of time the ScaleFinder algorithm can take to complete
	static const int maxNumPoints = 25;
	int linePoints[maxNumPoints][2];

};

#endif /* SRC_SCALELINE_H_ */
