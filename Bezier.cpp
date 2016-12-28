#include<gl/glut.h>
#include"Bezier.h"
#include<math.h>
void setPixel(int x, int y);

double C(int n, int k)  //计算多项式的系数C(n,k)  
{
	int i;
	double sum = 1;
	for (i = 1; i <= n; i++)
		sum *= i;
	for (i = 1; i <= k; i++)
		sum /= i;
	for (i = 1; i <= n - k; i++)
		sum /= i;
	return sum;
}

void Bezier::draw_bezier()
{
	//double m = abs(point[num-1].x - point[0].x);
	double m = 1000;
	for (int i = 0; i <= m; i++)
	{
		double x = 0, y = 0, bern;
		double t = (double)((double)i / (double)m);
		for (int k = 0; k<num; k++)
		{
			bern = C(num - 1, k)*pow(t, k)*pow(1 - t, num - 1 - k);//Bernstein基函数
			x += point[k].x*bern;
			y += point[k].y*bern;
			Coordinate p(x, y);
			bezier_position.push_back(p);
		}
		setPixel(x, y);
	}
}

float polyNomial(int k, int d, float u)
{
	if (d == 1)
	{
		if (u >= float(k) && u <= float(k + 1))
			return 1.0;
		else
			return 0.0;
	}
	else
		return (u - k) / (d - 1)*polyNomial(k, d - 1, u) + (k + d - u) / (d - 1)*polyNomial(k + 1, d - 1, u);
}

void B_spline::draw_b_spline()
{
	double u, du = 0.001;
	
	for (u= 2; u <=  num; u+=du)
	{
		double x = 0, y = 0, bern=0;
		//double t = (double)((double)i / (double)m);
		for (int k = 0; k<=num; k++)
		{
			//bern = C(num - 1, k)*pow(t, k)*pow(1 - t, num - 1 - k);//Bernstein基函数
			bern = polyNomial(k, 3, u);
			x += point[k].x*bern;
			y += point[k].y*bern;
			Coordinate p(x, y);
			b_position.push_back(p);
		}
		setPixel(x, y);
	}
}

void Bezier::clear_bezier()
{
	glColor3f(1, 1, 1);
	draw_bezier();
}

void B_spline::clear_b_spline()
{
	glColor3f(1, 1, 1);
	draw_b_spline();
}