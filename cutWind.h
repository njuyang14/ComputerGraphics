#ifndef _CUTWINDOW_H_
#define _CUTWINDOW_H_

#include<list>
#include<iostream>
using namespace std;
#include"Coordinate.h"

class cutWindow{
public:
	int x1, x2, y1, y2;//×ó£¬ÓÒ£¬ÉÏ£¬ÏÂ
	cutWindow(){ x1 = 300; x2 = 340; y1 = 260; y2 = 220; }
	void selectWindowSize(int sizeNo,int x,int y);
	void drawWind();
	int getCode(int x,int y);
};

#endif