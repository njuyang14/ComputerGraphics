#include<gl/glut.h>

void setPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}