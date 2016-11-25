#ifndef _POLYGON_H_
#define _POLYGON_H_

#include<vector>
#include<list>
#include<iostream>
#include"Line.h"
using namespace std;
#include"Coordinate.h"

typedef struct tagEDGE 
{
	double xi;
	double dx;
	int ymax;
}EDGE;

/*ֱ�߽ṹ*/
class Polygon{
private:
	int ymax;
	int ymin;
	list<Line> polygon_edge;
	vector<list<EDGE>> NET;//�±߱�
	list<EDGE> AET;//��߱�
public:
	friend void bresenham(int x0, int y0, int x1, int y1);//ֱ���㷨�������Ԫ���Ա����
	void create();
	void initNET();
	void initAET();
	void scanLineFill();
	void drawLine(int y);
	void erase_polygon();
};

#endif