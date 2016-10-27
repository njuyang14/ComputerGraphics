#include<gl/glut.h>
#include"Line.h"
#include<math.h>
void setPixel(int x,int y);

void Line::bresenham(int x0, int y0, int x1, int y1)
{
	double k = abs((y1 - y0) / (x1 - x0));

	Coordinate start(x0,y0);
	line_position.push_back(start);
	setPixel(x0,y0);

	/*init*/
	int tx = x1 - x0;
	int ty = y1 - y0;
	int p0 = 2 * ty - tx;

	if (k < 1)//Ð±ÂÊÐ¡ÓÚ1
	{
		while (x0 < x1)
		{
			if (p0 < 0)
			{
				x0++;
				Coordinate mid(x0,y0);
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

	Coordinate end(x1, y1);
	line_position.push_back(end);
	setPixel(x1,y1);
}