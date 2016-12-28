#ifndef _CONTROL_H_
#define _CONTROL_H_

#include<list>
#include"Line.h"
#include"Circle.h"
#include"Ellipse.h"
#include"Polygon.h"
#include"cutWind.h"
#include"Bezier.h"
#include"Cube.h"

class Control{
public:
	list<Line> all_line;
	list<Circle> all_circle;
	list<Ellipse> all_ellipse;
	list<Polygon> all_polygon;
	//int circle_num;
	cutWindow cutEvent;
	list<Bezier> all_bezier;
	list<B_spline> all_bspline;

	list<Cube> all_cube;
	Control(){
		//circle_num = 0;
	}
};


#endif