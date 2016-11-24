#include<gl/glut.h>
#include"Line.h"
#include<math.h>
void setPixel(int x,int y);

void Line::bresenham(int x0, int y0, int x1, int y1)
{
	start0 = x0;
	start1 = x1;
	end0 = y0;
	end1 = y1;

	/*扫描填充增量初始化*/
	dx_scan = (x0 - x1) / (y0 - y1);

	double k = ((double)(y1 - y0)) / ((double)(x1 - x0));
	Coordinate start(x0,y0);
	line_position.push_back(start);
	setPixel(x0,y0);

	/*init*/
	int tx = abs(x1 - x0);
	int ty = abs(y1 - y0);

	if (abs(k) < 1)//斜率小于1    
	{
		/*统一成由屏幕左端向右画图*/
		if (x0 > x1){
			int temp = x1;
			x1 = x0;
			x0 = temp;
			temp = y1;
			y1 = y0;
			y0 = temp;
		}
		int p0 = 2 * ty - tx;

		if (k > 0){
			while (x0 < x1)
			{
				if (p0 <= 0)
				{
					x0++;
					Coordinate mid(x0, y0);
					line_position.push_back(mid);

					p0 = p0 + 2 * ty;
				}
				else if (p0 > 0){
					x0++;
					y0++;
					Coordinate mid(x0, y0);
					line_position.push_back(mid);
					p0 = p0 + 2 * ty - 2 * tx;
				}
				setPixel(x0, y0);
			}
		}
		else//k<0
		{	
			while (x0<x1)
			{
				x0++;
				if (p0<=0)
				{
					p0 = p0 + 2 * ty;
				}
				else
				{
					y0--;
					p0 = p0 + 2 * ty - 2 * tx;
				}
				Coordinate mid(x0, y0);
				line_position.push_back(mid);
				setPixel(x0, y0);
			}
		}
	}
	else if (abs(k)>1)
	{
		/*统一成由屏幕左端向右画图*/
		if (y0 > y1){
			int temp = y1;
			y1 = y0;
			y0 = temp;
			temp = x1;
			x1 = x0;
			x0 = temp;
		}
		int p0 = 2 * tx - ty;

		if (k > 0){
			while (y0 < y1)
			{
				if (p0 <= 0)
				{
					y0++;
					Coordinate mid(x0, y0);
					line_position.push_back(mid);
					p0 = p0 + 2 * tx;
				}
				else if (p0 > 0){
					y0++;
					x0++;
					Coordinate mid(x0, y0);
					line_position.push_back(mid);
					p0 = p0 + 2 * tx - 2 * ty;
				}
				setPixel(x0, y0);
			}
		}
		else//k<0
		{
			while (y0<y1)
			{
				y0++;
				if (p0 <= 0)
				{
					p0 = p0 + 2 * tx;
				}
				else
				{
					x0--;
					p0 = p0 + 2 * tx - 2 * ty;
				}
				Coordinate mid(x0, y0);
				line_position.push_back(mid);
				setPixel(x0, y0);
			}
		}
	}
	Coordinate end(x1, y1);
	line_position.push_back(end);
	setPixel(x1,y1);
}

void Line::erase_line()
{
	glColor3f(1,1,1);
	bresenham(start0,end0,start1,end1);
}