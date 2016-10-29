#include<gl/glut.h>
#include"Ellipse.h"
#include<math.h>
void setPixel(int x, int y);

void Ellipse::bresenham_ellipse(int x0, int y0)
{
	int a, b;
	//cout << "Please input rx and ry: ";
	//cin >> a;
	//cin >> b;
	a = 100;
	b = 70;

	glBegin(GL_POINTS);
	GLfloat x = 0, y = b;
	GLfloat p0 = b ^ 2 - a^a^b - a ^ 2 / 4;
	while (a*a*y > b*b*x)
	{
		if (p0 < 0)
		{
			p0 = p0 + 2 * b*b*x + 3*b*b;
		}
		else
		{
			p0 = p0 + 2 * b*b*x - 2 * a*a*y + 3*b*b + 2 * a*a;
			y--;
		}
		x++;
		setPixel(x0 + x, y0 + y);
		setPixel(x0 + x, y0 - y);
		setPixel(x0 - x, y0 + y);
		setPixel(x0 - x, y0 - y);
	}

	p0 = b*b*(x + 1 / 2)*(x + 1 / 2) + a*a*(y - 1) - a*a*b*b;
	while (y > 0)
	{
		if (p0 > 0)
		{
			p0 = p0 - 2 * a*a*y + 3 * a*a;
		}
		else
		{
			p0 = p0 + 2 * b * b * x - 2 * y*a*a + 2 * b*b + 3 * a*a;
			x++;
		}
		y--;

		setPixel(x0 + x, y0 + y);
		setPixel(x0 + x, y0 - y);
		setPixel(x0 - x, y0 + y);
		setPixel(x0 - x, y0 - y);
	}
	glEnd();
	glFlush();
	cout << "draw end" << endl;
}