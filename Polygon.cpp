#include<gl/glut.h>
#include"Line.h"
#include"Polygon.h"
#include"Coordinate.h"
#include<math.h>
void setPixel(int x,int y);

void Polygon::create()
{
	Line l1, l2, l3, l4, l5, l6;
	l1.bresenham(2, 2, 2, 7);
	l2.bresenham(2, 2, 5, 1);
	l3.bresenham(5, 1, 10, 3);
	l4.bresenham(10, 3, 11, 8);
	l5.bresenham(5, 5, 11, 8);
	l6.bresenham(2, 7, 5, 5);
	polygon_edge.push_back(l1);
	polygon_edge.push_back(l2);
	polygon_edge.push_back(l3);
	polygon_edge.push_back(l4);
	polygon_edge.push_back(l5);
	polygon_edge.push_back(l6);
	/*计算扫描线最低和最高，ymin和ymax*/
	ymin = 2;
	ymax = 7;
	for (list<Coordinate>::iterator it = l1.line_position.begin(); it != l1.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l2.line_position.begin(); it != l2.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l2.line_position.begin(); it != l2.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l2.line_position.begin(); it != l2.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l2.line_position.begin(); it != l2.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l2.line_position.begin(); it != l2.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
}

void Polygon::initNET()
{
	vector<list<EDGE>> t_NET(ymax+1);
	for (list<Line>::iterator it = polygon_edge.begin(); it != polygon_edge.end(); it++)
	{
		int scan_line_no;//这条边的下端点
		EDGE t_edge;
		if (it->end0 < it->end1){
			t_edge.xi = it->start0;
			t_edge.ymax = it->end1;
			scan_line_no = it->end0;
		}
		else{
			t_edge.xi = it->start1;
			t_edge.ymax = it->end0;
			scan_line_no = it->end1;
		}
		t_edge.dx = it->dx_scan;
		t_NET[scan_line_no].push_back(t_edge);
	}
	NET = t_NET;
}

void Polygon::initAET()
{

}

void Polygon::scanLineFill()
{
	for (int i = ymin; i < ymax; i++)
	{

	}
}