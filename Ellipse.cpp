#include<gl/glut.h>
#include"Ellipse.h"
#include<math.h>
void setPixel(int x, int y);

void Ellipse::bresenham_ellipse(int x0, int y0,int a,int b)
{
	//cout << "Please input rx and ry: ";
	//cin >> a >> b;
	a = 100;
	b = 70;

	start = x0;
	end = y0;
	rx = a;
	ry = b;

	glBegin(GL_POINTS);
	GLfloat x = 0, y = b;
	GLfloat p0 = b * b - a*a*b + a * a / 4;
	glVertex2f(x0 + x, y0 + y);
	glVertex2f(x0 + x, y0 - y);
	while (a*a*y > b*b*x)
	{
		x++;
		if (p0 < 0)
		{
			p0 = p0 + 2 * b*b*x + b*b;
		}
		else
		{
			y--;
			p0 = p0 + 2 * b*b*x - 2 * a*a*y + b*b;
		}

		glVertex2f(x0 + x, y0 + y);
		glVertex2f(x0 + x, y0 - y);
		glVertex2f(x0 - x, y0 + y);
		glVertex2f(x0 - x, y0 - y);
	}

	p0 = b*b*(x + 0.5)*(x + 0.5) + a*a*(y - 1)*(y-1) - a*a*b*b;//(y-1)*(y-1)?
	while (y > 0)
	{
		y--;
		if (p0 > 0)
		{
			p0 = p0 - 2 * a*a*y + a*a;
		}
		else
		{
			x++;
			p0 = p0 + 2 * b * b * x - 2 * y*a*a + a*a;
		}

		glVertex2f(x0 + x, y0 + y);
		glVertex2f(x0 + x, y0 - y);
		glVertex2f(x0 - x, y0 + y);
		glVertex2f(x0 - x, y0 - y);
	}
	glEnd();
	glFlush();
}

void Ellipse::erase_ellipse()
{
	glColor3f(1,1,1);
	bresenham_ellipse(start,end,rx,ry);
}