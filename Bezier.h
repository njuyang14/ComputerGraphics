#ifndef _BEZIER_H_
#define _BEZIER_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"
#include"Line.h"

class Bezier{
public:
	Bezier(){ num = 0; }
	int num = 0;//控制点数
	Coordinate point[1000];//控制点
	list<Coordinate> bezier_position;//曲线上的点
	//list<Line> line_array;//轨迹直线

	void draw_bezier();//绘制
	void clear_bezier();
};

class B_spline{
public:
	B_spline(){ num = 0; }
	int num = 0;//控制点数
	Coordinate point[1000];//控制点
	list<Coordinate> b_position;//曲线上的点
	//list<Line> line_array;//轨迹直线

	void draw_b_spline();//绘制
	void clear_b_spline();
};
#endif