#include"common.h"
#include"Control.h"

int MENU;
char DRAW_MODE;

/*draw line*/
int line_click = 0;
int circle_click = 0;
int startx, endx, starty, endy;
int rx, ry;

/*#include<WinUser.h>
#include<windows.h>

//HWND edit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE, 0, 0, 100, 10, hWnd, NULL, hInstance, NULL);
//�����༭��hWnd�Ǹ����ھ��,hInstance�ǳ����� ShowWindow(edit,SW_SHOW); 
//��ʾ�༭�� ��ȡ�ı���GetWindowText();
*/

Control myDraw;
extern Control myDraw;

void SelectMenu(int value)
{
	MENU = value;
	line_click = 0;
	circle_click = 0;
	/*if (value==2)
	{
		cout << "input rx,ry: ";
		cin >> rx >> ry;
	}*/
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

				/*��bresenham����ֱ�ߣ���������Control::myDraw��*/
				Line new_line;
				new_line.bresenham(startx, starty, endx, endy);
				myDraw.all_line.push_back(new_line);
			}
		}
		break;
	}
	case 1:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{//�������������꣬Բ�ĺ�Բ������һ��
			if (circle_click == 0){
				startx = x;
				starty = 480 - y;
				circle_click = 1;
			}
			else if (circle_click == 1){
				endx = x;
				endy = 480 - y;
				circle_click = 0;

				/*��bresenham����Բ����������Control::myDraw��*/
				Circle new_circle;
				new_circle.bresenham_circle(startx, starty, endx, endy);
				myDraw.all_circle.push_back(new_circle);
			}
			//cout << "press left" << endl;
		}
		break;
	}
	case 2:
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{	
			startx = x;
			endy = 480 - y;

			Ellipse new_ellipse;
			new_ellipse.bresenham_ellipse(startx, endy, rx, ry);
			cout << "draw end" << endl;
		}
		break;
	}
	case 10:
	{
		glClear(GL_COLOR_BUFFER_BIT);
		break;
	}
	default:{break; }
	}
}


void myDisplay()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);//ת������640*480
	glClear(GL_COLOR_BUFFER_BIT);

	/*set menu*/
	int menu_id = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("Draw a line", 0);
	glutAddMenuEntry("Draw a circle", 1);
	glutAddMenuEntry("Draw a ellipse", 2);
	glutAddMenuEntry("Clear screen",10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//glutKeyboardFunc(PressKeyboard);
	glutMouseFunc(PressMouse);
}