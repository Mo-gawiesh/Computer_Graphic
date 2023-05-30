#include <iostream>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include<GL/glut.h>
#include <cmath>
#include <stdlib.h>

#define PI 3.1459
GLfloat R = 800.0 / 600; //Форматное соотношение
GLfloat w = 60; //Ширина мирового окна
GLfloat h; //Высота мирового окна
GLfloat l, r, b, t; //Параметры мирового окна
GLfloat f = 30.0;
GLfloat x = 0;
GLfloat x1 = 2;
int mode = 1, mode1 = 2;

void init(void)
{
	h = w / R; l = -w / 2; r = w / 2; b = -h / 2; t = h / 2; //Расчет параметров миро-вого окна
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei W, GLsizei H)
{
	if (R > W / H) glViewport(0, 0, W, W / R);
	else glViewport(0, 0, H * R, H);
}

void fig0(void)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-10.0, -6.0);
	glVertex2f(-10.0, 6.0);
	glVertex2f(-2.0, 6.0);
	glVertex2f(-2.0, -6.0);
	glEnd();
}
void fig1(void)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(10.0, 6.0);
	glVertex2f(10.0, -6.0);
	glVertex2f(2.0, -6.0);
	glVertex2f(2.0, 6.0);
	glEnd();
}

void scene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glScalef(x, -x, x);
	fig0();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	//x+=0.5; if(x==2.0) x=0;
	if (mode == 1)
	{
		x += 0.5;
	}
	else if (mode == 2)
	{
		x -= 0.5;
	}
	if (x == 2.0)
	{
		mode = 2;
	}
	else if (x == 0.5)
	{
		mode = 1;
	}

	glPushMatrix();
	glScalef(x1, -x1, x1);
	fig1();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	//x1-=0.5; if(x1==0.0) x1=2.0;
	if (mode1 == 1)
	{
		x1 += 0.5;
	}
	else if (mode1 == 2)
	{
		x1 -= 0.5;
	}
	if (x1 == 2.0)
	{
		mode1 = 2;
	}
	else if (x1 == 0.5)
	{
		mode1 = 1;
	}
	//usleep(100000);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Lab 2 first task gawish");
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutIdleFunc(scene);
	init();
	glutMainLoop();
}