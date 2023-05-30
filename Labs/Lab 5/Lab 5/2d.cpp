#include <gl/glut.h>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <C:\\Users\\Moe-gawish\\Desktop\\toool\\Лаба 5\\GLAUX.H>
#include "stb_image.h"
#pragma comment(lib, "C:\\Users\\Moe-gawish\\Desktop\\toool\\Лаба 5\\GLAUX.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
GLfloat angle = 180, plusangle = 0;
GLfloat angle2 = 0, plusangle2 = 0;
int ch1 = 0, ch2 = 0;
GLuint list = 0, list2 = 0;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	AUX_RGBImageRec* image = auxDIBImageLoadA("E:\\study\\2 course\\4 Semester\\Computer Graphic\\Комп.графика\\Лабы\\лаба 5\\a.bmp"); 
	//для загрузки в оперативную память изображения
	AUX_RGBImageRec* image2 = auxDIBImageLoadA("E:\\study\\2 course\\4 Semester\\Computer Graphic\\Комп.графика\\Лабы\\лаба 5\\a.bmp");
	AUX_RGBImageRec* image3 = auxDIBImageLoadA("E:\\study\\2 course\\4 Semester\\Computer Graphic\\Комп.графика\\Лабы\\лаба 5\\a.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	list = glGenLists(1); //генерирование одного или более незадействованных индексов.
	glNewList(list, GL_COMPILE); //Определение дисплейного списка
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	// грань f0 (основание)
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(1, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(1, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glEnd();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image3->sizeX, image3->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image3->data);
	// грань f1 (задняя стенка)
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0, 2);
	glVertex3f(1, 0, 0);
	glTexCoord2f(2, 0);
	glVertex3f(1, 1, 0);
	glEnd();
	// грань f2 (передняя стенка)
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 1);
	glTexCoord2f(0, 2);
	glVertex3f(1, 0, 1);
	glTexCoord2f(2, 0);
	glVertex3f(1, 1, 1);
	glEnd();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2->sizeX, image2->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image2->data);
	// грань f3 (верхушка)
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 0, 0);
	glEnd();
	// грань f4 (левая стенка)
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 1);
	glEnd();
	glEndList(); //конец списка list_1
	// грань f5 (правая стенка)
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(1, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(1, 1, 0);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 0, 1);
	glEnd();
	glEndList();
	list2 = glGenLists(1); //генерирование одного или более незадействованных индексов.
	glNewList(list2, GL_COMPILE);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
	glEnd();

	glEndList();
}
void showAxis() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
	glEnd();
}


void myDisplay()
{
	glPushMatrix(); //Сохраняем VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //вместе с очисткой буфера цвета предусмотреть очистку буфера глубины
	glEnable(GL_DEPTH_TEST); //включение режима удаления невидимых (проверка глубины)
	gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0); // VM=Fwe // позиция наблюдателя
	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 }; // Источник света в CKw
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); // Позиция ис-точника света будет преобразована в CKe
	glPushMatrix(); //Сохраняем VM=Fwe
	glRotatef(angle2, 0, 1, 0);//поворот ск на заданный угол
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	glBegin(GL_LINES); // Рисуем направление к источнику света в CKe
	glColor3f(1, 1, 1); glVertex3f(myLightPosition[0], myLightPosition[1],myLightPosition[2]); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPopMatrix(); // Восстанавливаем VM=Fwe
	glEnable(GL_LIGHTING); // Включение расчета освещенности
	glEnable(GL_LIGHT0); // включаем этот конкретный источник
	glPushMatrix(); //Сохраняем VM=Fwe
	glRotatef(angle, 0, 1, 0);//поворот ск на заданный угол
	GLfloat myDiffuse[] = { 0.50754, 0.50754, 0.50754, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw
	GLfloat myShininess[] = { 51.2 };
	glMaterialfv(GL_FRONT, GL_SHININESS, myShininess);
	GLfloat myAmbient[] = { 0.19225, 0.19225, 0.19225, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, myAmbient);
	GLfloat mySpecular[] = { 0.508273, 0.508273, 0.508273, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mySpecular);
	glCallList(list); //установка состояния, и команды рисования
	glPopMatrix(); // Восстанавливаем VM=Fwe
	glDisable(GL_LIGHTING); //Выключаем освещение
	glCallList(list2); //установка состояния, и команды рисования
	glPopMatrix();
	glutSwapBuffers();
}

void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}

void myIdle()
{
	angle += plusangle; if (angle > 360.0) angle = 0;
	angle2 += plusangle2; if (angle2 > 360.0) angle2 = 0;
	glutPostRedisplay();
}

void keys(unsigned char key, int x, int y)
{
	if (key == '0') {

		if (ch1 % 2 == 0) plusangle = 0.1;
		else plusangle = 0;
		ch1++;
	}
	else if (key == 'l') {
		if (ch2 % 2 == 0) plusangle2 = 0.1;
		else plusangle2 = 0;
		ch2++;
	}

	if (key == 'f') {
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	else if (key == 'b') {
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
	}
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //объект излучает свет согласно заданной текстуре
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //объект излучет свет согласно заданной текстуре
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //устанавливая режим дисплея в функции main(), предусмотрено использование буфера глубины
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lab 5 Gawish");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(mouseButton);
	glutKeyboardFunc(keys);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
}
