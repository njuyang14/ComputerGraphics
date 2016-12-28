#include<gl/glut.h>
#include"Cube.h"
#include<math.h>
void setPixel(int x, int y);

Cube::Cube(point3d v,int edge_len)
{
	vertex3d[0] = v;
	vertex3d[1] = { v.x, v.y, v.z-edge_len };
	vertex3d[2] = { v.x+edge_len, v.y, v.z - edge_len };
	vertex3d[3] = { v.x+edge_len, v.y, v.z };
	vertex3d[4] = { v.x, v.y-edge_len, v.z };
	vertex3d[5] = { v.x, v.y-edge_len, v.z - edge_len };
	vertex3d[6] = { v.x+edge_len, v.y - edge_len, v.z - edge_len };
	vertex3d[7] = { v.x+edge_len, v.y - edge_len, v.z };
	center = { (vertex3d[0].x + vertex3d[6].x) / 2, (vertex3d[0].y + vertex3d[6].y) / 2, (vertex3d[0].z + vertex3d[6].z) / 2 };
	//½«ÈıÎ¬×ø±ê×ª»»³É¶şÎ¬
	for (int i = 0; i < 8; i++)
		vertex2d[i] = vertex3d[i];
}

point3d Cube::point3d_2d(point3d v,int axle,double rotate)
{
	point3d result;
	double angle = (3.1415926 / 180)*rotate;
	if (axle == 1)//ÈÆxÖá
	{

	}
	else if (axle == 2)//ÈÆyÖá
	{

	}
	else if (axle == 3)//ÈÆzÖá
	{

	}
	return result;
}

void Cube::draw_cube()
{
	Line l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11;
	l0.bresenham(vertex2d[0].x, vertex2d[0].y, vertex2d[1].x, vertex2d[1].y);
	l1.bresenham(vertex2d[1].x, vertex2d[1].y, vertex2d[2].x, vertex2d[2].y);
	l2.bresenham(vertex2d[2].x, vertex2d[2].y, vertex2d[3].x, vertex2d[3].y);
	l3.bresenham(vertex2d[3].x, vertex2d[3].y, vertex2d[0].x, vertex2d[0].y);
	l4.bresenham(vertex2d[4].x, vertex2d[4].y, vertex2d[5].x, vertex2d[5].y);
	l5.bresenham(vertex2d[5].x, vertex2d[5].y, vertex2d[6].x, vertex2d[6].y);
	l6.bresenham(vertex2d[6].x, vertex2d[6].y, vertex2d[7].x, vertex2d[7].y);
	l7.bresenham(vertex2d[7].x, vertex2d[7].y, vertex2d[4].x, vertex2d[4].y);
	l8.bresenham(vertex2d[0].x, vertex2d[0].y, vertex2d[4].x, vertex2d[4].y);
	l9.bresenham(vertex2d[1].x, vertex2d[1].y, vertex2d[5].x, vertex2d[5].y);
	l10.bresenham(vertex2d[2].x, vertex2d[2].y, vertex2d[6].x, vertex2d[6].y);
	l11.bresenham(vertex2d[3].x, vertex2d[3].y, vertex2d[7].x, vertex2d[7].y);
	cube_line.push_back(l0);
	cube_line.push_back(l1);
	cube_line.push_back(l2);
	cube_line.push_back(l3);
	cube_line.push_back(l4);
	cube_line.push_back(l5);
	cube_line.push_back(l6);
	cube_line.push_back(l7);
	cube_line.push_back(l8);
	cube_line.push_back(l9);
	cube_line.push_back(l10);
	cube_line.push_back(l11);
}