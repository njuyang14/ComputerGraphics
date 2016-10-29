#include<gl/glut.h>
#include"Circle.h"
#include<math.h>
void setPixel(int x, int y);

void Circle::bresenham_circle(int x0, int y0, int x1, int y1)
{
	glBegin(GL_POINTS);
	GLfloat r = sqrt(pow(abs(y1 - y0), 2) + pow(abs(x1 - x0), 2));
	GLfloat x, y;
	x = 0, y = r;
	GLfloat p0 = 5 / 4 - r;
	Circle_coordinate p(x0, y0, x1, y1);
	circle_position.push_back(p);
	glVertex2f(x0+x, y0+y);
	while (x<y)
	{
		x++;
		if (p0 < 0)
		{
			p0 = p0 + 2 * x + 1;
		}
		else
		{
			p0 = p0 + 2 * x + 1 - 2 * y;
			y--;
		}
		glVertex2f(x0 + x, y0 + y);
		glVertex2f(x0 + x, y0 - y);
		glVertex2f(x0 - x, y0 + y);
		glVertex2f(x0 - x, y0 - y);
		glVertex2f(x0 + y, y0 + x);
		glVertex2f(x0 + y, y0 - x);
		glVertex2f(x0 - y, y0 + x);
		glVertex2f(x0 - y, y0 - x);
	}
	glEnd();
	glFlush();
}