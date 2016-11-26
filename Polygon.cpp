#include<gl/glut.h>
#include"Line.h"
#include"Polygon.h"
#include"Coordinate.h"
#include<math.h>
#include<algorithm>
#include <functional>
void setPixel(int x,int y);

void Polygon::create1()
{
	Line l1, l2, l3, l4, l5, l6;
	/*
	l1.bresenham(2, 2, 2, 7);
	l2.bresenham(2, 2, 5, 1);
	l3.bresenham(5, 1, 10, 3);
	l4.bresenham(10, 3, 11, 8);
	l5.bresenham(5, 5, 11, 8);
	l6.bresenham(2, 7, 5, 5);
	*/
	l1.bresenham(220, 220, 220, 270);
	l2.bresenham(220, 220, 250, 210);
	l3.bresenham(250, 210, 300, 230);
	l4.bresenham(300, 230, 310, 280);
	l5.bresenham(250, 250, 310, 280);
	l6.bresenham(220, 270, 250, 250);

	polygon_edge.push_back(l1);
	polygon_edge.push_back(l2);
	polygon_edge.push_back(l3);
	polygon_edge.push_back(l4);
	polygon_edge.push_back(l5);
	polygon_edge.push_back(l6);
	/*����ɨ������ͺ���ߣ�ymin��ymax*/
	ymin = l1.line_position.begin()->y;
	ymax = l1.line_position.begin()->y;
	for (list<Coordinate>::iterator it = l1.line_position.begin(); it != l1.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l2.line_position.begin(); it != l2.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l3.line_position.begin(); it != l3.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l4.line_position.begin(); it != l4.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l5.line_position.begin(); it != l5.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
	for (list<Coordinate>::iterator it = l6.line_position.begin(); it != l6.line_position.end(); it++){
		if (it->y < ymin){ ymin = it->y; }
		if (it->y > ymax){ ymax = it->y; }
	}
}

void Polygon::initNET()
{
	vector<list<EDGE>> t_NET(ymax+1);
	for (list<Line>::iterator it = polygon_edge.begin(); it != polygon_edge.end(); it++)
	{
		int scan_line_no;//�����ߵ��¶˵�
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

bool compByXi(EDGE &e1, EDGE &e2)
{
	return (e1.xi < e2.xi);
}

bool ifValid(EDGE e, int y) 
{  //�жϱ��Ƿ�ʧЧ
	return (e.ymax == y);
}

void Polygon::drawLine(int y)
{
	int intersection = AET.size();
	int line_num = intersection / 2;
	for (list<EDGE>::iterator it = AET.begin(); it != AET.end();it++)
	{
		list<EDGE>::iterator it_2nd = it;
		it_2nd++;
		for (int i = it->xi; i < it_2nd->xi; i++)
			setPixel(i, y);
		it++;
	}
}

void Polygon::scanLineFill()
{
	for (int y = ymin; y < ymax;)
	{
		for (list<EDGE>::iterator it = NET[y].begin(); it != NET[y].end(); it++)
			AET.push_back(*it);

		if (y != ymin)//��һ�β���Ҫ����xi
		{
			for (list<EDGE>::iterator it = AET.begin(); it != AET.end(); it++)
				it->xi += it->dx;
		}
		AET.sort(compByXi);

		drawLine(y);//������ǰ��߱�����߶�

		y++;
		//AET.remove_if(bind2nd(ptr_fun(ifValid), y));//ɾ����Ч�ı�y=ymax
		for (list<EDGE>::iterator it = AET.begin(); it != AET.end();)
		{
			list<EDGE>::iterator it2 = it;
			it++;
			if (it2->ymax == y)AET.erase(it2);
		}
	}
}

void Polygon::cut(cutWindow&cw)
{
	for (list<Line>::iterator it = polygon_edge.begin(); it != polygon_edge.end(); it++)
		it->cut(cw);
}