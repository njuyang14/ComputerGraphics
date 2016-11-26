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
	dx_scan = ((double)(x0 - x1)) / ((double)(y0 - y1));

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
	line_position.clear();
	bresenham(start0,end0,start1,end1);
}

void Line::panning(int x,int y)
{
	erase_line();
	glColor3f(1,0,0);
	line_position.clear();
	int dx = x - (start0 + start1) / 2;
	int dy = y - (end0 + end1) / 2;
	bresenham(start0 + dx, end0 + dy, start1 + dx, end1 + dy);
}

void Line::zooming()
{

}

void Line::cut(cutWindow &cw)
{
	erase_line();
	bool done = false, draw = false;
	while (!done)
	{
		int code1 = cw.getCode(start0, end0);
		int code2 = cw.getCode(start1, end1);
		if (!(code1|code2))//两点都在裁剪窗口内
		{
			done = true;
			draw = true;
		}
		else
		{
			if ((code1&code2)!=0)//线段绝对不在区域内
			{
				done = true;
			}
			else
			{
				if (!code2)//让第一个点在裁剪框内
				{//交换两点
					int temp = start0;
					start0 = start1;
					start1 = temp;
					temp = end0;
					end0 = end1;
					end1 = temp;
					temp = code1;
					code1 = code2;
					code2 = temp;
				}
				double k = ((double)(end1 - end0)) / ((double)(start1 - start0));//斜率
				//判断第二个点的位置
				if (code2 & 0x0001) { //左侧
					end1 += (cw.x1 - start1)*k;
					start1 = cw.x1;
				}
				else if (code2 & 0x0010) { //右侧
					end1 += (cw.x2 - start1)*k;
					start1 = cw.x2;
				}
				else if (code2 & 0x0100) { //下方
					if (start1 != start0)
						start1 += (cw.y2 - end1) / k;
					end1 = cw.y2;
				}
				else if (code2 & 0x1000) { //上方
					if (start1 != start0)
						start1 += (cw.y1 - end1) / k;
					end1 = cw.y1;
				}
			}
		}
	}
	if (draw){
		glColor3f(0, 1, 0);
		bresenham(start0, end0, start1, end1);
	}
}