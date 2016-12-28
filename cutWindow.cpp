#include<gl/glut.h>
#include"Line.h"
#include"Polygon.h"
#include"Coordinate.h"
void setPixel(int x, int y);

int cutWindow::getCode(int x,int y)
{
	int result = 0x0000;
	if (x<x1)
		result |= 0x0001;//вС
	if (x>x2)
		result |= 0x0010;//ср
	if (y>y1)
		result |= 0x1000;//ио
	if (y<y2)
		result |= 0x0100;//об
	return result;
}

void cutWindow::selectWindowSize(int sizeNo,int x,int y)
{
	switch (sizeNo)
	{
	case 11:{x1 = x - 125; x2 = x + 125; y1 = y + 125; y2 = y - 125; break; }
	case 12:{x1 = x - 150; x2 = x + 150; y1 = y + 150; y2 = y - 150; break; }
	case 13:{x1 = x - 275; x2 = x + 275; y1 = y + 175; y2 = y - 175; break; }
	}
	//drawWind();
}

void cutWindow::drawWind()
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
	glFlush();
}