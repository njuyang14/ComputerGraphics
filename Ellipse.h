#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"

/*ֱ�߽ṹ*/
class Ellipse{
private:
	list<Ellipse_coordinate> ellipse_position;
public:
	void bresenham_ellipse(int x0, int y0);
};

#endif