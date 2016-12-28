#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"

class Circle{
private:
	list<Circle_coordinate> circle_position;
	int start0, end0, start1, end1;
public:
	void bresenham_circle(int x0, int y0, int x1, int y1);
	void erase_circle();
	void panning(int x, int y);
	void rotating(int basex, int basey, int rotatex, int rotatey);
	void zooming(int basex, int basey);
};

#endif