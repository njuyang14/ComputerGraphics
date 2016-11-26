#include"common.h"
#include"Control.h"

int MENU;
char DRAW_MODE;

/*draw line*/
int line_click = 0;
int circle_click = 0;
int startx, endx, starty, endy;
int rx, ry;
//椭圆长轴短轴

Control myDraw;
extern Control myDraw;

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
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
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
				/*用bresenham画出圆，并保存在Control::myDraw中*/
				Circle new_circle;
				new_circle.bresenham_circle(startx, starty, endx, endy);
				myDraw.all_circle.push_front(new_circle);
			}
			//cout << "press left" << endl;
		}
		break;
	}
	case 4:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{	
			startx = x;
			endy = 480 - y;

			glColor3f(1, 0, 0);
			Ellipse new_ellipse;
			new_ellipse.bresenham_ellipse(startx, endy, rx, ry);
			myDraw.all_ellipse.push_front(new_ellipse);
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
	}
	case 11:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			myDraw.cutEvent.selectWindowSize(11, startx, endy);
		}
	}
	case 12:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			startx = x;
			endy = 480 - y;
			myDraw.cutEvent.selectWindowSize(12, startx, endy);
		}
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
	}
	case 100:
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);
		break;
	}
	default:{break; }
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

	/*set menu*/
	int menu_id = glutCreateMenu(SelectMenu);
	glutAddSubMenu("直线", line_submenu);
	glutAddSubMenu("圆", circle_submenu);
	glutAddSubMenu("椭圆", ellipse_submenu);
	glutAddSubMenu("多边形", polygon_submenu);
	glutAddSubMenu("裁剪窗口", cut_submenu);
	glutAddMenuEntry("Clear screen",100);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//glutKeyboardFunc(PressKeyboard);
	glutMouseFunc(PressMouse);
}