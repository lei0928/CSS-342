/*
 * dragon.h
 *
 *  Created on: Oct 22, 2018
 *      Author: Lei
 */

// Dragon Class
#ifndef DRAGON_H_
#define DRAGON_H_

#include "Turtle.h"
#include <iostream>
#include <math.h>

using namespace std;

//-------------------------------------------------------------------
// Dragon curve:
//    -- leftCurve: draws a left Dragon arrowhead at a given level
//    -- rightCurve: draws a right Dragon arrowhead at a given level
//
// Assumptions:
//    -- Level 1 is defined as an integer.
//    -- Distance d is define as a float.
//    -- Outputs are in postscript format.
//-------------------------------------------------------------------

class Dragon : Turtle {
public:
	Dragon(float initX=0.0, float initY=0.0, float initAngle=0.0);
	void leftCurve(int l, float d);  // draw a level-1 left curve with distance d
	void rightCurve(int l, float d); // draw a level-1 right curve with distance d
};

#endif /* DRAGON_H_ */
