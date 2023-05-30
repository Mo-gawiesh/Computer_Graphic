#include<GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
void init();
void draw();

const GLfloat A = 1.0f;
const GLfloat B = 1.0f;
const GLfloat w = 1.0f;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("First task for first lab Gaiwsh");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}

void init()
{
	glClearColor(0.9, 0.9, 0.9, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-8.0, 8.0, -2.0, 2.0);
}

void draw()
{
	GLfloat x, y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glViewport(0, 0, 640, 480);
	//draw x and y axis
	glBegin(GL_LINES);
	glVertex2f(-8.0, 0.0);
	glVertex2f(8.0, 0.0);
	glVertex2f(0.0, 2.0);
	glVertex2f(0.0, -2.0);
	glEnd();
	//draw x(t) = Asin(wt)
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (x = -2 * M_PI - 2; x <= 2 * M_PI + 2; x += M_PI / 180)
	{
		y = A * sin(w * x);
		glVertex2f(x, y);
	}
	glEnd();
	//draw y(t) = Bcos(wt)
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (x = -2 * M_PI - 2; x <= 2 * M_PI + 2; x += M_PI / 180)
	{
		y = B * cos(w * x);
		glVertex2f(x, y);
	}
	glEnd();
	glFlush();
}