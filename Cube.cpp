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
	//将三维坐标转换成二维
	for (int i = 0; i < 8; i++)
		vertex2d[i] = vertex3d[i];
	//rotate_cube(30,30,0);//测试旋转
	//rotate_cube(-30, -30, 0);
}

point3d Cube::point3d_2d(point3d v,int axle,double rotate)
{
	point3d result = { 0, 0, 0 };
	double angle = (3.1415926 / 180)*rotate;
	if (axle == 1)//绕x轴
	{
		result.x = v.x;
		result.y = (double)v.y * cos(angle) - (double)v.z * sin(angle);
		result.z = (double)v.y * sin(angle) + (double)v.z * cos(angle);
	}
	else if (axle == 2)//绕y轴
	{
		result.x = (double)v.x * cos(angle) + (double)v.z * sin(angle);
		result.y = v.y;
		result.z = (double)(-v.x) * sin(angle) + (double)v.z * cos(angle);
	}
	else if (axle == 3)//绕z轴
	{
		result.x = (double)v.x * cos(angle) - (double)v.y * sin(angle);
		result.y = (double)v.x * sin(angle) + (double)v.y * cos(angle);
		result.z = v.z;

	}
	return result;
}

void Cube::draw_cube()
{
	int maxDeep = 0,cnt=0;
	for (int i = 0; i < 8; i++)
		if (vertex2d[maxDeep].z < vertex2d[i].z){
			maxDeep = i;//寻找深度最大的顶点
			cnt++;
		}

	Line l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11;
	if (maxDeep != 6 && maxDeep != 7)
	    l0.bresenham(vertex2d[0].x, vertex2d[0].y, vertex2d[1].x, vertex2d[1].y);
	if (maxDeep != 4 && maxDeep != 7)
	    l1.bresenham(vertex2d[1].x, vertex2d[1].y, vertex2d[2].x, vertex2d[2].y);
	if (maxDeep != 4 && maxDeep != 5)
	    l2.bresenham(vertex2d[2].x, vertex2d[2].y, vertex2d[3].x, vertex2d[3].y);
	if (maxDeep != 5 && maxDeep != 6)
	    l3.bresenham(vertex2d[3].x, vertex2d[3].y, vertex2d[0].x, vertex2d[0].y);
	if (maxDeep != 2 && maxDeep != 3)
	    l4.bresenham(vertex2d[4].x, vertex2d[4].y, vertex2d[5].x, vertex2d[5].y);
	if (maxDeep != 0 && maxDeep != 3)
	    l5.bresenham(vertex2d[5].x, vertex2d[5].y, vertex2d[6].x, vertex2d[6].y);
	if (maxDeep != 0 && maxDeep != 1)
	    l6.bresenham(vertex2d[6].x, vertex2d[6].y, vertex2d[7].x, vertex2d[7].y);
	if (maxDeep != 2 && maxDeep != 1)
	    l7.bresenham(vertex2d[7].x, vertex2d[7].y, vertex2d[4].x, vertex2d[4].y);
	if (maxDeep != 2 && maxDeep != 6)
	    l8.bresenham(vertex2d[0].x, vertex2d[0].y, vertex2d[4].x, vertex2d[4].y);
	if (maxDeep != 3 && maxDeep != 7)
	    l9.bresenham(vertex2d[1].x, vertex2d[1].y, vertex2d[5].x, vertex2d[5].y);
	if (maxDeep != 0 && maxDeep != 4)
	    l10.bresenham(vertex2d[2].x, vertex2d[2].y, vertex2d[6].x, vertex2d[6].y);
	if (maxDeep != 5 && maxDeep != 1)
	    l11.bresenham(vertex2d[3].x, vertex2d[3].y, vertex2d[7].x, vertex2d[7].y);

	
	
	/*glColor3f(1, 1, 1);
	if (maxDeep == 6||maxDeep==7)
		l0.bresenham(vertex2d[0].x, vertex2d[0].y, vertex2d[1].x, vertex2d[1].y);
	if (maxDeep==4||maxDeep==7)
		l1.bresenham(vertex2d[1].x, vertex2d[1].y, vertex2d[2].x, vertex2d[2].y);
	if (maxDeep == 4 || maxDeep == 5)
		l2.bresenham(vertex2d[2].x, vertex2d[2].y, vertex2d[3].x, vertex2d[3].y);
	if (maxDeep == 5 || maxDeep == 6)
		l3.bresenham(vertex2d[3].x, vertex2d[3].y, vertex2d[0].x, vertex2d[0].y);
	if (maxDeep == 2 || maxDeep == 3)
		l4.bresenham(vertex2d[4].x, vertex2d[4].y, vertex2d[5].x, vertex2d[5].y);
	if (maxDeep == 0 || maxDeep == 3)
		l5.bresenham(vertex2d[5].x, vertex2d[5].y, vertex2d[6].x, vertex2d[6].y);
	if (maxDeep == 0 || maxDeep == 1)
		l6.bresenham(vertex2d[6].x, vertex2d[6].y, vertex2d[7].x, vertex2d[7].y);
	if (maxDeep == 2 || maxDeep == 1)
		l7.bresenham(vertex2d[7].x, vertex2d[7].y, vertex2d[4].x, vertex2d[4].y);
	if (maxDeep == 2 || maxDeep == 6)
	    l8.bresenham(vertex2d[0].x, vertex2d[0].y, vertex2d[4].x, vertex2d[4].y);
	if (maxDeep == 3 || maxDeep == 7)
	    l9.bresenham(vertex2d[1].x, vertex2d[1].y, vertex2d[5].x, vertex2d[5].y);
	if (maxDeep == 0 || maxDeep == 4)
	    l10.bresenham(vertex2d[2].x, vertex2d[2].y, vertex2d[6].x, vertex2d[6].y);
	if (maxDeep == 5 || maxDeep == 1)
	    l11.bresenham(vertex2d[3].x, vertex2d[3].y, vertex2d[7].x, vertex2d[7].y);
		*/
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

void Cube::rotate_cube(int q0,int q1,int q2)
{
	for (int i = 0; i < 8; i++)
		vertex2d[i] = point3d_2d(vertex2d[i],1,q0);//绕x轴旋转q0度
	for (int i = 0; i < 8; i++)
		vertex2d[i] = point3d_2d(vertex2d[i], 2, q1);//绕y轴旋转q1度
	for (int i = 0; i < 8; i++)
		vertex2d[i] = point3d_2d(vertex2d[i], 3, q2);//绕y轴旋转q2度
}

void Cube::erase_cube()
{
	glColor3f(1, 1, 1);
	for (list<Line>::iterator it = cube_line.begin(); it != cube_line.end(); it++){
		it->bresenham(it->start0, it->end0, it->start1, it->end1);
	}
	cube_line.clear();
}