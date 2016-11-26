#ifndef _CONTROL_H_
#define _CONTROL_H_

#include<list>
#include"Line.h"
#include"Circle.h"
#include"Ellipse.h"
#include"Polygon.h"
#include"cutWind.h"

class Control{
public:
	list<Line> all_line;
	list<Circle> all_circle;
	list<Ellipse> all_ellipse;
	list<Polygon> all_polygon;
	cutWindow cutEvent;
};


#endif