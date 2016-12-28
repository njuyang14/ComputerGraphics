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
	int num = 0;//���Ƶ���
	Coordinate point[1000];//���Ƶ�
	list<Coordinate> bezier_position;//�����ϵĵ�
	//list<Line> line_array;//�켣ֱ��

	void draw_bezier();//����
	void clear_bezier();
};

class B_spline{
public:
	B_spline(){ num = 0; }
	int num = 0;//���Ƶ���
	Coordinate point[1000];//���Ƶ�
	list<Coordinate> b_position;//�����ϵĵ�
	//list<Line> line_array;//�켣ֱ��

	void draw_b_spline();//����
	void clear_b_spline();
};
#endif