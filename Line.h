#ifndef _LINE_H_
#define _LINE_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"
#include"cutWind.h"

/*ֱ�߽ṹ*/
class Line{
public:
	int start0, end0, start1, end1;
	double dx_scan;//ɨ�����x����
	list<Coordinate> line_position;
	void bresenham(int x0,int y0,int x1,int y1);
	void panning(int x,int y);
	void rotating();
	void zooming();
	void cut(cutWindow &cw);
	void erase_line();
};

#endif