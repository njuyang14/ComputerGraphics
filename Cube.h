#ifndef _CUBE_H_
#define _CUBE_H_

#include<list>
#include<vector>
#include<iostream>
using namespace std;
#include"Coordinate.h"
#include"Line.h"

struct point3d{
	double x;
	double y;
	double z;
};


class Cube{
public:
	/*立方体下标对应
	 1 ____________2
	  /|                /|
	/  |              /  |
0/__ |5______/___|6
  |    /          3|   /
  |  /              | /
4|/__________|/ 7
	*/
	point3d vertex3d[8];
	point3d vertex2d[8];
	point3d center;
	list<Line> cube_line;

	Cube(){}
	Cube(point3d v0,int edge_len);
	point3d point3d_2d(point3d v,int axle,double rotate);//坐标转换,ratate是旋转的角度
	void draw_cube();
	void rotate_cube(int q0, int q1, int q2);//旋转
	void erase_cube();//擦除
};

#endif