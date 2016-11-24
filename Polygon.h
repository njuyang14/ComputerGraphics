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
	vector<list<EDGE>> AET;//��߱�
public:
	void create();
	void initNET();
	void initAET();
	void scanLineFill();
	void erase_polygon();
};

#endif