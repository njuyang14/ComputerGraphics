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

/*直线结构*/
class Polygon{
private:
	int ymax;
	int ymin;
	list<Line> polygon_edge;
	vector<list<EDGE>> NET;//新边表
	vector<list<EDGE>> AET;//活动边表
public:
	void create();
	void initNET();
	void initAET();
	void scanLineFill();
	void erase_polygon();
};

#endif