#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"

/*ֱ�߽ṹ*/
class Ellipse{
public:
	list<Ellipse_coordinate> ellipse_position;
	int start, end, rx, ry;
	void bresenham_ellipse(int x0, int y0,int a,int b);
	void erase_ellipse();
};

#endif