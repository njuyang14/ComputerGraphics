#include<list>
#include<iostream>
using namespace std;

/*点的坐标*/
class Coordinate{
public:
	int x;
	int y;
	Coordinate(int i,int j){
		x = i;
		y = j;
	}
};

/*直线结构*/
class Line{
private:
	list<Coordinate> line_position;
public:
	void bresenham(int x0,int y0,int x1,int y1);
};