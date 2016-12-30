#include"common.h"
#include"Control.h"
#include<math.h>
#include<fstream>
int MENU;
char DRAW_MODE;

list<Line> temp_line;
list<Circle> temp_circle;
list<Ellipse> temp_ellipse;

/*draw line*/
int line_click = 0;
int circle_click = 0;
int startx, endx, starty, endy;//坐标参数
int rx, ry;//椭圆长轴短轴
int oldx, oldy;//鼠标拖动时鼠标位置
bool firstClick = true;//拖动鼠标时第一次点击鼠标
bool circleFinish = false;
int spline_click = 0;//曲线点击数
int edit_bezier=0;//拖动bezier曲线

Control myDraw;
extern Control myDraw;

double distance(double x0, double y0, double x1, double y1){
	return (double)sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
}

void SelectMenu(int value)
{
	MENU = value;
	line_click = 0;
	circle_click = 0;
	if (value==1)
	{
		list<Line>::iterator it = myDraw.all_line.begin();
		it->erase_line();
		myDraw.all_line.erase(it);
	}
	else if (value == 3)
	{
		list<Circle>::iterator it = myDraw.all_circle.begin();
		it->erase_circle();
		myDraw.all_circle.erase(it);
	}
	else if (value == 5)
	{
		list<Ellipse>::iterator it = myDraw.all_ellipse.begin();
		it->erase_ellipse();
		myDraw.all_ellipse.erase(it);
	}
	else if (value == 6||value==16||value==15)
	{
		glColor3f(1, 0, 0);
		Polygon newplg;
		newplg.create1();	
		myDraw.all_polygon.push_front(newplg);
	}
	else if (value == 7)
	{
		list<Polygon>::iterator it = myDraw.all_polygon.begin();
		it->initNET();
		it->scanLineFill();
	}
	else if (value == 9)//line rotate
	{
		//myDraw.all_line.begin()->panning();
	}
	else if (value == 10)//line zoom
	{
	}
	else if (value == 14)//line cut
	{
		myDraw.all_line.begin()->cut(myDraw.cutEvent);
	}
	else if (value == 17)//polygon cut
	{
		myDraw.all_polygon.begin()->cut(myDraw.cutEvent);
	}
	else if (value == 18)//new bezier
	{
		if (spline_click == 0)
		{
			Bezier newBezier;
			myDraw.all_bezier.push_front(newBezier);
		}
	}
	else if (value == 19){}
	else if (value == 20){}
	else if (value == 21){
		if (spline_click == 0)
		{
			B_spline sp;
			myDraw.all_bspline.push_front(sp);
		}
	}
	else if (value == 27)//保存
	{
		ofstream  file("my_picture.txt", ios::out);
		file << myDraw.all_line.size() << endl;
		for (list<Line>::iterator it = myDraw.all_line.begin(); it != myDraw.all_line.end(); it++)
			file << it->start0 << " " << it->end0 << " " << it->start1 << " " << it->end1 << endl;
		file << myDraw.all_circle.size() << endl;
		for (list<Circle>::iterator it = myDraw.all_circle.begin(); it != myDraw.all_circle.end(); it++)
			file << it->start0 << " " << it->end0 << " " << it->start1 << " " << it->end1 << endl;
		file << myDraw.all_ellipse.size() << endl;
		for (list<Ellipse>::iterator it = myDraw.all_ellipse.begin(); it != myDraw.all_ellipse.end(); it++)
			file << it->start << " " << it->end << " " << it->rx << " " << it->ry << endl;
		file << myDraw.all_polygon.size() << endl;
		for (list<Polygon>::iterator it = myDraw.all_polygon.begin(); it != myDraw.all_polygon.end(); it++){
			file << it->polygon_edge.size() << endl;
			for (list<Line>::iterator it1 = it->polygon_edge.begin(); it1 != it->polygon_edge.end(); it1++)
				file << it1->start0 << " " << it1->end0 << " " << it1->start1 << " " << it1->end1 << endl;
		}
		file << myDraw.all_bezier.size() << endl;
		for (list<Bezier>::iterator it = myDraw.all_bezier.begin(); it != myDraw.all_bezier.end(); it++){
			int b_size = it->num;
			file << b_size<<endl;
			for (int i = 0; i < b_size; i++){
				file << it->point[i].x << " " << it->point[i].y << endl;
			}
		}
		file << myDraw.all_bspline.size() << endl;
		for (list<B_spline>::iterator it = myDraw.all_bspline.begin(); it != myDraw.all_bspline.end(); it++){
			int b_size = it->num;
			file << b_size << endl;
			for (int i = 0; i < b_size; i++){
				file << it->point[i].x << " " << it->point[i].y << endl;
			}
		}
		file << myDraw.all_cube.size() << endl;
		for (list<Cube>::iterator it = myDraw.all_cube.begin(); it != myDraw.all_cube.end(); it++){
			for (int i = 0; i < 8; i++)
			{
				file << it->vertex2d[i].x << " " << it->vertex2d[i].y << " " << it->vertex2d[i].z << endl;
			}
		}

	}
	else if (value == 28)//打开
	{
		//清空内存中的图元链表
		myDraw.all_bezier.clear();
		myDraw.all_bspline.clear();
		myDraw.all_circle.clear();
		myDraw.all_cube.clear();
		myDraw.all_ellipse.clear();
		myDraw.all_line.clear();
		myDraw.all_polygon.clear();

		ifstream file("my_picture.txt");
		int unit_num;

		//直线
		file >> unit_num;
		for (int i = 0; i < unit_num; i++)
		{
			Line l;
			file >> l.start0 >> l.end0 >> l.start1 >> l.end1;
			myDraw.all_line.push_front(l);
			glColor3f(1, 0, 0);
			l.bresenham(l.start0, l.end0, l.start1, l.end1);
		}
		//圆
		file >> unit_num;
		for (int i = 0; i < unit_num; i++)
		{
			Circle c;
			file >> c.start0 >> c.end0 >> c.start1 >> c.end1;
			myDraw.all_circle.push_front(c);
			glColor3f(1, 0, 0);
			c.bresenham_circle(c.start0, c.end0, c.start1, c.end1);
		}
		//椭圆
		file >> unit_num;
		for (int i = 0; i < unit_num; i++)
		{
			Ellipse e;
			file >> e.start >> e.end >> e.rx >> e.ry;
			myDraw.all_ellipse.push_front(e);
			glColor3f(1, 0, 0);
			e.bresenham_ellipse(e.start, e.end, e.rx, e.ry);
		}
		//多边形
		file >> unit_num;
		for (int i = 0; i < unit_num; i++)
		{
			Polygon p;
			int l_num;//多边形边数
			file >> l_num;
			for (int j = 0; j < l_num; j++){
				Line l;
				file >> l.start0 >> l.end0 >> l.start1 >> l.end1;
				p.polygon_edge.push_front(l);
				glColor3f(1, 0, 0);
				l.bresenham(l.start0, l.end0, l.start1, l.end1);
			}
			myDraw.all_polygon.push_front(p);
		}
		//Bezier曲线
		file >> unit_num;
		for (int i = 0; i < unit_num; i++){
			int ctrl_num;//控制点数
			file >> ctrl_num;
			Bezier b;
			for (int j = 0; j < ctrl_num; j++){
				file >> b.point[j].x >> b.point[j].y;
				setPixel(b.point[j].x, b.point[j].y);
			}
			b.draw_bezier();
			myDraw.all_bezier.push_front(b);
		}
		//B样条曲线
		file >> unit_num;
		for (int i = 0; i < unit_num; i++){
			int ctrl_num;//控制点数
			file >> ctrl_num;
			B_spline b;
			for (int j = 0; j < ctrl_num; j++){
				file >> b.point[j].x >> b.point[j].y;
				setPixel(b.point[j].x, b.point[j].y);
			} 
			b.draw_b_spline();
			myDraw.all_bspline.push_front(b);
		}
		//立方体
		file >> unit_num;
		for (int i = 0; i < unit_num; i++){
			Cube c;
			for (int j = 0; j < 8; j++){
				file >> c.vertex2d[j].x >> c.vertex2d[j].y >> c.vertex2d[j].z;
			}
			c.draw_cube();
			myDraw.all_cube.push_front(c);
		}
	}
}

void PressKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':{
		DRAW_MODE = 'q';
		//setPixel(100,100);
		line_click = 0;
		cout << "draw a line." << endl; 
		break;
	}
	case 'w':{
		DRAW_MODE = 'w';
		circle_click = 0;
		cout << "draw a circle" << endl; 
		break; 
	}
	case 'e':{
		DRAW_MODE = 'e';
		cout << "draw a ellipse" << endl;
		break;
	}
	default:{
		cout << "TODO:add function to draw more graphics." << endl;
		break;
	}
	}
}

void PressMouse(int button, int state, int x, int y)
{
	switch (MENU)
	{//TODO: draw more graphic
	case 0:{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (line_click == 0){
				startx = x;
				starty = 480 - y;
				line_click = 1;
			}
			else if (line_click == 1){
				endx = x;
				endy = 480 - y;
				line_click = 0;

				glColor3f(1, 0, 0);
				/*用bresenham画出直线，并保存在Control::myDraw中*/
				Line new_line;
				new_line.bresenham(startx, starty, endx, endy);
				myDraw.all_line.push_front(new_line);
			}
		}
		break;
	}
	case 2:
	{
		/*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{//鼠标接收两个坐标，圆心和圆上任意一点
			if (circle_click == 0){
				startx = x;
				starty = 480 - y;
				circle_click = 1;
			}
			else if (circle_click == 1){
				endx = x;
				endy = 480 - y;
				circle_click = 0;

				glColor3f(1, 0, 0);
				Circle new_circle;
				new_circle.bresenham_circle(startx, starty, endx, endy);
				myDraw.all_circle.push_front(new_circle);
			}
			//cout << "press left" << endl;
		}*/
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if (firstClick){
				firstClick = false;
				startx = x; starty = 480 - y;
			}
			else{
				oldx = x; oldy = 480 - y;
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
  			firstClick = true;
			myDraw.all_circle.push_front(*temp_circle.begin());
			temp_circle.clear();
		}
		break;
	}
	case 4:
	{
		/*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{	
			startx = x;
			endy = 480 - y;

			glColor3f(1, 0, 0);
			Ellipse new_ellipse;
			new_ellipse.bresenham_ellipse(startx, endy, rx, ry);
			myDraw.all_ellipse.push_front(new_ellipse);
		}*/
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if (firstClick){
				firstClick = false;
				startx = x; starty = 480 - y;
			}
			else{
				oldx = x; oldy = 480 - y;
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
			firstClick = true;
			myDraw.all_ellipse.push_front(*temp_ellipse.begin());
			temp_ellipse.clear();
		}
		break;
	}
	case 8:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			myDraw.all_line.begin()->panning(startx,endy);
		}
		break;
	}
	case 11:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			myDraw.cutEvent.selectWindowSize(11, startx, endy);
			myDraw.cutEvent.drawWind();
		}
		break;
	}
	case 12:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			myDraw.cutEvent.selectWindowSize(12, startx, endy);
			myDraw.cutEvent.drawWind();
		}
		break;
	}
	case 13:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			myDraw.cutEvent.selectWindowSize(13, startx, endy);
			myDraw.cutEvent.drawWind();
		}
		break;
	}
	case 18:
	{
		if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			myDraw.all_bezier.begin()->point[spline_click].x = startx;
			myDraw.all_bezier.begin()->point[spline_click].y = endy;
			myDraw.all_bezier.begin()->num++;
			setPixel(startx, endy);
			spline_click++;
		}
		else if (button == GLUT_MIDDLE_BUTTON&&state == GLUT_DOWN)
		{
			glColor3f(1, 0, 0);
			myDraw.all_bezier.begin()->draw_bezier();
			spline_click = 0;
		}
		break;
	}
	case 20:
	{
		if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			for (edit_bezier = 0; edit_bezier < myDraw.all_bezier.begin()->num; edit_bezier++)
			{
				int srcx = myDraw.all_bezier.begin()->point[edit_bezier].x;
				int srcy = myDraw.all_bezier.begin()->point[edit_bezier].y;
				if (distance(startx,endy,srcx,srcy)<10)
				{
					break;
				}
			}
		}
		break;
	}
	case 21:
	{
		if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			myDraw.all_bspline.begin()->point[spline_click].x = startx;
			myDraw.all_bspline.begin()->point[spline_click].y = endy;
			myDraw.all_bspline.begin()->num++;
			setPixel(startx, endy);
			spline_click++;
		}
		else if (button == GLUT_MIDDLE_BUTTON&&state == GLUT_DOWN)
		{
			glColor3f(1, 0, 0);
			myDraw.all_bspline.begin()->draw_b_spline();
			spline_click = 0;
		}
		break;
	}
	case 23:
	{
		if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			for (edit_bezier = 0; edit_bezier < myDraw.all_bspline.begin()->num; edit_bezier++)
			{
				int srcx = myDraw.all_bspline.begin()->point[edit_bezier].x;
				int srcy = myDraw.all_bspline.begin()->point[edit_bezier].y;
				if (distance(startx, endy, srcx, srcy)<10)
				{
					break;
				}
			}
		}
		break;
	}
	case 24://cube
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (line_click == 0){
				startx = x;
				starty = 480 - y;
				line_click = 1;
			}
			else if (line_click == 1){
				endx = x;
				endy = 480 - y;
				line_click = 0;

				glColor3f(1, 0, 0);
				point3d p = { startx, starty, 0 };//cube第0个顶点
				int edge_len = abs(endx - startx);
				Cube cube(p, edge_len);
				cube.draw_cube();
				myDraw.all_cube.push_front(cube);
			}
		}
		break;
	}
	case 26:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if (line_click == 0){
				startx = x;
				starty = 480 - y;
				line_click = 1;
			}
			else if (line_click == 1){
				endx = x;
				endy = 480 - y;
				line_click = 0;

				if (startx - endx > 0){
					myDraw.all_cube.begin()->erase_cube();
					myDraw.all_cube.begin()->rotate_cube(0,5, 0);
				}
				else if (startx - endx < 0){
					myDraw.all_cube.begin()->erase_cube();
					myDraw.all_cube.begin()->rotate_cube(0,-5, 0);
				}
				if (starty - endy>0){
					myDraw.all_cube.begin()->erase_cube();
					myDraw.all_cube.begin()->rotate_cube(5,0 , 0);
				}
				else if (starty - endy < 0){
					myDraw.all_cube.begin()->erase_cube();
					myDraw.all_cube.begin()->rotate_cube(-5, 0, 0);
				}
				glColor3f(1, 0, 0);
				myDraw.all_cube.begin()->draw_cube();
			}
		}
		break;
	}
	case 100:
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);
		break;
	}
	default:{break; }
	}  
}

void motion(int x, int y)
{
	switch (MENU){
	case 2:
	{//circle zoom
		y = 480 - y;
		if ((!firstClick)){
			if (temp_circle.begin() != temp_circle.end())
			{
				list<Circle>::iterator it = temp_circle.begin();
				it->erase_circle();
				temp_circle.erase(it);
			}
		}
		glColor3f(1, 0, 0);
		Circle new_circle;
		new_circle.bresenham_circle(startx, starty, x, y);
		temp_circle.push_front(new_circle);
		break;
	}
	case 4:
	{//ellipse zoom
		y = 480 - y;
		if ((!firstClick)){
			if (temp_ellipse.begin() != temp_ellipse.end())
			{
				list<Ellipse>::iterator it = temp_ellipse.begin();
				it->erase_ellipse();
				temp_ellipse.erase(it);
			}
		}
		glColor3f(1, 0, 0);
		Ellipse new_ellipse;
		new_ellipse.bresenham_ellipse(startx, starty, abs(x-startx), abs(y-starty));
		temp_ellipse.push_front(new_ellipse);
		break;
	}
	case 20:
	{
		y = 480 - y;
		glColor3f(1, 1, 1);
		setPixel(myDraw.all_bezier.begin()->point[edit_bezier].x, myDraw.all_bezier.begin()->point[edit_bezier].y);
		myDraw.all_bezier.begin()->clear_bezier();
		//重绘
		glColor3f(1, 0, 0);
		setPixel(x, y);
		myDraw.all_bezier.begin()->point[edit_bezier].x = x;
		myDraw.all_bezier.begin()->point[edit_bezier].y = y;
		myDraw.all_bezier.begin()->draw_bezier();
		break;
	}
	case 23:
	{
		y = 480 - y;
		glColor3f(1, 1, 1);
		setPixel(myDraw.all_bspline.begin()->point[edit_bezier].x, myDraw.all_bspline.begin()->point[edit_bezier].y);
		myDraw.all_bspline.begin()->clear_b_spline();
		//重绘
		glColor3f(1, 0, 0);
		setPixel(x, y);
		myDraw.all_bspline.begin()->point[edit_bezier].x = x;
		myDraw.all_bspline.begin()->point[edit_bezier].y = y;
		myDraw.all_bspline.begin()->draw_b_spline();
		break;
	}
	}
}

void myDisplay()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);//转换坐标640*480
	glClear(GL_COLOR_BUFFER_BIT);

	int line_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("绘制",0);
	glutAddMenuEntry("删除", 1);
	glutAddMenuEntry("平移", 8);
	glutAddMenuEntry("旋转", 9);
	glutAddMenuEntry("缩放", 10);
	glutAddMenuEntry("裁剪", 14);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int circle_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("绘制", 2);
	glutAddMenuEntry("删除", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int ellipse_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("绘制", 4);
	glutAddMenuEntry("删除", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/*polygon submenu 的子菜单  */
	int poly_sub_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("多边形1", 6);
	glutAddMenuEntry("多边形2", 15);
	glutAddMenuEntry("多边形3", 16);

	int polygon_submenu = glutCreateMenu(SelectMenu);
	glutAddSubMenu("绘制", poly_sub_submenu);
	glutAddMenuEntry("填充", 7);
	glutAddMenuEntry("裁剪", 17);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int cut_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("小", 11);
	glutAddMenuEntry("中", 12);
	glutAddMenuEntry("大", 13);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int bezier_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("绘制", 18);
	glutAddMenuEntry("删除", 19);
	glutAddMenuEntry("编辑", 20);

	int bspline_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("绘制", 21);
	glutAddMenuEntry("删除", 22);
	glutAddMenuEntry("编辑", 23);

	int solid_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("绘制", 24);
	glutAddMenuEntry("删除", 25);
	glutAddMenuEntry("变换", 26);

	int file_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("保存", 27);
	glutAddMenuEntry("打开", 28);

	/*set menu*/
	int menu_id = glutCreateMenu(SelectMenu);
	glutAddSubMenu("直线", line_submenu);
	glutAddSubMenu("圆", circle_submenu);
	glutAddSubMenu("椭圆", ellipse_submenu);
	glutAddSubMenu("多边形", polygon_submenu);
	glutAddSubMenu("裁剪窗口", cut_submenu);
	glutAddSubMenu("Bezier曲线", bezier_submenu);
	glutAddSubMenu("B样条曲线", bspline_submenu);
	glutAddSubMenu("正六面体", solid_submenu);
	glutAddSubMenu("菜单", file_submenu);
	glutAddMenuEntry("Clear screen",100);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//glutKeyboardFunc(PressKeyboard);
	glutMouseFunc(PressMouse);
	glutMotionFunc(motion);
}