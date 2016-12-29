#include"common.h"
#include"Control.h"
#include<math.h>
int MENU;
char DRAW_MODE;

list<Line> temp_line;
list<Circle> temp_circle;
list<Ellipse> temp_ellipse;

/*draw line*/
int line_click = 0;
int circle_click = 0;
int startx, endx, starty, endy;//�������
int rx, ry;//��Բ�������
int oldx, oldy;//����϶�ʱ���λ��
bool firstClick = true;//�϶����ʱ��һ�ε�����
bool circleFinish = false;
int spline_click = 0;//���ߵ����
int edit_bezier=0;//�϶�bezier����

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
				/*��bresenham����ֱ�ߣ���������Control::myDraw��*/
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
				point3d p = { startx, starty, 0 };//cube��0������
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
		//�ػ�
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
		//�ػ�
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
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);//ת������640*480
	glClear(GL_COLOR_BUFFER_BIT);

	int line_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("����",0);
	glutAddMenuEntry("ɾ��", 1);
	glutAddMenuEntry("ƽ��", 8);
	glutAddMenuEntry("��ת", 9);
	glutAddMenuEntry("����", 10);
	glutAddMenuEntry("�ü�", 14);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int circle_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("����", 2);
	glutAddMenuEntry("ɾ��", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int ellipse_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("����", 4);
	glutAddMenuEntry("ɾ��", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/*polygon submenu ���Ӳ˵�  */
	int poly_sub_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("�����1", 6);
	glutAddMenuEntry("�����2", 15);
	glutAddMenuEntry("�����3", 16);

	int polygon_submenu = glutCreateMenu(SelectMenu);
	glutAddSubMenu("����", poly_sub_submenu);
	glutAddMenuEntry("���", 7);
	glutAddMenuEntry("�ü�", 17);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int cut_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("С", 11);
	glutAddMenuEntry("��", 12);
	glutAddMenuEntry("��", 13);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int bezier_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("����", 18);
	glutAddMenuEntry("ɾ��", 19);
	glutAddMenuEntry("�༭", 20);

	int bspline_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("����", 21);
	glutAddMenuEntry("ɾ��", 22);
	glutAddMenuEntry("�༭", 23);

	int solid_submenu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("����", 24);
	glutAddMenuEntry("ɾ��", 25);
	glutAddMenuEntry("�任", 26);

	/*set menu*/
	int menu_id = glutCreateMenu(SelectMenu);
	glutAddSubMenu("ֱ��", line_submenu);
	glutAddSubMenu("Բ", circle_submenu);
	glutAddSubMenu("��Բ", ellipse_submenu);
	glutAddSubMenu("�����", polygon_submenu);
	glutAddSubMenu("�ü�����", cut_submenu);
	glutAddSubMenu("Bezier����", bezier_submenu);
	glutAddSubMenu("B��������", bspline_submenu);
	glutAddSubMenu("��������", solid_submenu);
	glutAddMenuEntry("Clear screen",100);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//glutKeyboardFunc(PressKeyboard);
	glutMouseFunc(PressMouse);
	glutMotionFunc(motion);
}