#include"common.h"

/*function to init screen*/
void myDisplay();

int main(int arg,char **argv)
{
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My Graphic Draw System");
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}