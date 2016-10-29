#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"

class Circle{
private:
	list<Circle_coordinate> circle_position;
public:
	void bresenham_circle(int x0, int y0, int x1, int y1);
};

#endif