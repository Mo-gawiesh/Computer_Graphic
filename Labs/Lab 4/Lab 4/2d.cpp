#include <GL/glut.h>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

GLfloat angle = 0, plusangle = 0; // инициализация переменных, угол для источника
GLfloat angle2 = 0, plusangle2 = 0; //угол для объекта
bool isPressed1 = false, isPressed2 = false;

void init(void)// инициализация проекта
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // очищаем цветом цвета буфера цветов
	glMatrixMode(GL_PROJECTION); // задаем матрицу проекции текущей
	glLoadIdentity(); // установим единичную матрицу
	gluPerspective(60, 1, 1, 10); // здесь определяем перскпетиву проекции
	glMatrixMode(GL_MODELVIEW);// здесь задаем матрицу модель-вид текущей
	glLoadIdentity();// снова установим единичную матрицу
}

void showAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
	glEnd();
}

void fig()//рисование полигональной сетки
{
	glBegin(GL_POLYGON); //1
	glNormal3f(0.577, 0.577, 0.577);//устанавливает «текущую нормаль», которая применяется ко всем вершинам, последовательно
	//пересылаемым в конвейер с помощью glVertex3f(vx, vy, vz). Эта нормаль остается текущей вплоть до ее изменения при следующем вызове glNormal3f(…).
	glVertex3f(1, 0, 0); glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_POLYGON); //2
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);//3
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); glVertex3f(0, 1, 0);
	glEnd();

	glBegin(GL_POLYGON);//4
	glNormal3f(0, -1, 0);
	glVertex3f(1, 0, 0); glVertex3f(0, 0, 1); glVertex3f(0, 0, 0);
	glEnd();
}

void myDisplay()
{
	glPushMatrix(); //сохранит в стеке VM=1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Очищается фон
	glEnable(GL_DEPTH_TEST); // Тест на глубниу включается
	gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);// Фиксируем положение камеры наблюдателя
	/*
	1-3) позиция наблюдателя
	4-6) точка, в которую направлен взгяд наблюдателя
	7-9) вектор, задающий плоскость ze ye и направление оси ze
	*/

	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 };// Определим световой источник
	glEnable(GL_LIGHTING);// Включение расчета освещенности
	glEnable(GL_LIGHT0);// включаем этот конкретный источник

	glPushMatrix();//сохранит в стеке VM=1
	glRotatef(angle2, 0, 1, 0);//поворот ск на заданный угол
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);// Здесь изменим конкретный источник света в CKe
	glBegin(GL_LINES);
	glColor3f(1, 1, 1); glVertex3f(myLightPosition[0], myLightPosition[1], myLightPosition[2]); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();//вытолкнет из вершины стека текущую матрицу и заменит ее сохраненной VM = 1

	glPushMatrix();//сохранит в стеке VM=1
	glRotatef(angle, 0, 1, 0);//поворот ск на заданный угол
	fig();//рисование фигуры
	glPopMatrix(); //вытолкнет из вершины стека текущую матрицу и заменит ее сохраненной VM = 1

	glDisable(GL_LIGHTING);// Освещение выключается
	showAxis();//рисование осей
	glPopMatrix(); //вытолкнет из вершины стека текущую матрицу и заменит ее сохраненной VM = 1
	glutSwapBuffers();//переключение буферов
}

void myReshape(int width, int height)// для изменения размеров порта просмотра
{
	if (width / height < 1) glViewport(0, 0, width, width); //устанавливается положение и размеры порта просмотра
	else glViewport(0, 0, height, height);
}

void myIdle() //если никаких действий не происходит
{
	angle += plusangle; if (angle > 360.0) angle = 0; //увеличение угла
	angle2 += plusangle2; if (angle2 > 360.0) angle2 = 0;
	glutPostRedisplay();//перерисовка окна
}

void keys(unsigned char key, int x, int y) //для идентификации нажатых клавиш
{
	if (key == 'o') { //вращение источника света
		if (!isPressed1) plusangle = 0.1; //если 
		else plusangle = 0;
		isPressed1 = !isPressed1;
	}
	else if (key == 'l') {
		if (!isPressed2) plusangle2 = 0.1;
		else plusangle2 = 0;
		isPressed2 = !isPressed2;
	}

	if (key == 'f') {//визуализация (не)лицевых граней
		glCullFace(GL_BACK);//нелицевые грани
		glEnable(GL_CULL_FACE);
	}
	else if (key == 'b') {
		glCullFace(GL_FRONT);//лицевые грани
		glEnable(GL_CULL_FACE);
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//инициализация библиотеки GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // включаем режим отображения
	//установка режима двойной буферизации (в одном буфере кадра выполняется рисование, другой отображается)
	glutInitWindowSize(800, 800); //установка размеров window
	glutInitWindowPosition(0, 0);  //далее вызываем созданные нами функции
	glutCreateWindow("Lab 4 Gawish"); //инициализируется открытие экранного окна window
	glutDisplayFunc(myDisplay);;//функция регистрируется как функция обратного вызова для события открытия или обновления экранного окна
	glutKeyboardFunc(keys);// регистрирует функцию func, которая должна вызываться всякий раз, когда нажата клавиши на клавиатуре
	glutReshapeFunc(myReshape);//регистрирует функцию func,которая должна вызываться всякий раз, когда изменяются размеры окна или оно перемещено
	glutIdleFunc(myIdle);// регистрирует функцию, которая будет выполняться в отсутствии событий
	init();//вызов функции инициализии
	glutMainLoop(); // запускаем главный цикл GLUT
}
