/*
 * dragon.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: Lei
 */

// Dragon member function definitions
#include "dragon.h"

const int RIGHT = -90;
const int LEFT = 90;

//---------------Dragon Arrowhead----------------------------
Dragon::Dragon(float initX, float initY, float initAngle)
    : Turtle(initX, initY, initAngle) {
}

//---------------Member functions----------------------------
//-----------private functions inheritated from Turtle-------
//private: from Turtle
//  void draw(float d);         // draw line by distance d
//  void move(float d);         // simply move by distance c
//  void turn(float d);         // turn by angle a

//-------------------leftCurve------------------------------
// draw a level-1 left curve with distance d
void Dragon::leftCurve(int level, float d) {
	if (level == 1){
		draw(d);
		turn(LEFT);
		draw(d);
		turn(LEFT);
	} else if (level > 1) {
	    leftCurve(level - 1, d);
	    turn(LEFT);
	    rightCurve(level - 1, d);
	    turn(LEFT);
	} else {
		draw(d);
	}
}

//-------------------rightCurve------------------
// draw a level-1 right curve with distance d
void Dragon::rightCurve(int level, float d) {
	if (level == 1){
		turn(RIGHT);
		draw(d);
		turn(RIGHT);
		draw(d);
	} else if(level > 1) {
	    turn(RIGHT);
		leftCurve(level - 1, d);
	    turn(RIGHT);
	    rightCurve(level - 1, d);
	} else {
		draw(d);
	}
}



