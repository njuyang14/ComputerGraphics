#include"common.h"
#include"Control.h"

char DRAW_MODE;

/*draw line*/
int line_click = 0;
int circle_click = 0;
int startx, endx, starty, endy;


Control myDraw;
extern Control myDraw;


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
		circle_click = 0;
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
	switch (DRAW_MODE)
	{//TODO: draw more graphic
	case 'q':{
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
	case 'w':
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
			cout << "press left" << endl;
		}
		break;
	}
	case 'e':
	{
		
		int xc, yc;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{	
			xc = x;
			yc = 480 - y;
			Ellipse new_ellipse;
			//new_ellipse.bresenham_ellipse(xc,yc);
			new_ellipse.bresenham_ellipse(100, 100);
		}
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
	glutKeyboardFunc(PressKeyboard);
	glutMouseFunc(PressMouse);
	//glFlush();
}