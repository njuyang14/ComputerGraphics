#include<list>
#include<iostream>
using namespace std;

/*�������*/
class Coordinate{
public:
	int x;
	int y;
	Coordinate(int i,int j){
		x = i;
		y = j;
	}
};

/*ֱ�߽ṹ*/
class Line{
private:
	list<Coordinate> line_position;
public:
	void bresenham(int x0,int y0,int x1,int y1);
};