#ifndef _LINE_H_
#define _LINE_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"

/*ֱ�߽ṹ*/
class Line{
private:
	list<Coordinate> line_position;
public:
	void bresenham(int x0,int y0,int x1,int y1);
};

#endif