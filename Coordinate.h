#ifndef _COORDINATE_H_
#define _COORDINATE_H_

/*�������*/
class Coordinate{
public:
	int x;
	int y;
	//int size;
	Coordinate(){}
	Coordinate(int i, int j){
		x = i;
		y = j;
	}
};

class Circle_coordinate{
public:
	int x, y, x0,y0;//Բ�ĺ�Բ������һ������
	Circle_coordinate(int i,int j,int i0,int j0){
		x = i;
		y = j;
		x0 = i0;
		y0 = j0;
	}
};

class Ellipse_coordinate{
public:
	int x, y, a, b;
	Ellipse_coordinate(int i,int j,int aa,int bb){
		x = i;
		y = j;
		a = aa;
		b = bb;
	}
};

#endif