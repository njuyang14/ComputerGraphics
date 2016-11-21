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
				myDraw.all_line.push_back(new_line);
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
				myDraw.all_circle.push_back(new_circle);
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
			myDraw.all_ellipse.push_back(new_ellipse);
		}
		break;
	}
	case 10:
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
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int circle_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("绘制", 2);
	glutAddMenuEntry("删除", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int ellipse_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("绘制", 4);
	glutAddMenuEntry("删除", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/*set menu*/
	int menu_id = glutCreateMenu(SelectMenu);
	glutAddSubMenu("Draw a line", line_submenu);
	glutAddSubMenu("Draw a circle", circle_submenu);
	glutAddSubMenu("Draw a ellipse", ellipse_submenu);
	glutAddMenuEntry("Clear screen",10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//glutKeyboardFunc(PressKeyboard);
	glutMouseFunc(PressMouse);
}