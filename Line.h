#ifndef _LINE_H_
#define _LINE_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"

/*直线结构*/
class Line{
public:
	int start0, end0, start1, end1;
	double dx_scan;//扫描填充x增量
	list<Coordinate> line_position;
	void bresenham(int x0,int y0,int x1,int y1);
	void erase_line();
};

#endif