#include <gl/glut.h>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <C:\\Users\\Moe-gawish\\Desktop\\toool\\Лаба 5\\GLAUX.H>
#include "stb_image.h"
#pragma comment(lib, "C:\\Users\\Moe-gawish\\Desktop\\toool\\Лаба 5\\GLAUX.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
#include <Windows.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <iostream>
#include <atlconv.h>
#include <string>
#include <cmath>

float thickness = 2;
float h1, h2, h3;
float angle_light = 15.0;
float angle = 0, angle_plus = 0;
bool check = false;
int list = 0;

void draw_K();
void draw_T();
void draw_I();
void draw_Z();

void init(void) {
    float R = 640.0 / 480.0;
    AUX_RGBImageRec* pImage = auxDIBImageLoad(L"C:/Users/Moe-gawish/source/repos/Lab 8/З.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    double eyeX = 1.0, eyeY = 5.0, eyeZ = 20.0;
    double centerX = 1.0, centerY = 0.0, centerZ = 0.0;
    double upX = 0.0, upY = 1.0, upZ = 0.0;
    float n = 1.0f, f = 50.0f;

    glClearColor(0.9, 0.9, 0.9, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, 1, 1, 120);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    draw_K();
    draw_T();
    draw_I();
    draw_Z();
    glEndList();
}

void myDisplay()
{
    float LightPos_1[] = { 10.0, 15.0, 20.0, 1.0 };
    float myDiffuse[] = { 0.15, 0.15, 0.2, 1 }; float myShininess[] = { 10.00 };
    float myAmbient[] = { 0.01, 0.05, 0.11, 1 };
    float mySpecular[] = { 0.33, 0.33, 0.52, 1 };
    glPushMatrix(); //Сохраняем VM = 1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //вместе с очисткой буфера цветапредусмотреть очистку буфера глубины
        glEnable(GL_DEPTH_TEST); //включение режима удаления невидимых (проверка глубины)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw
    glMaterialfv(GL_FRONT, GL_SHININESS, myShininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, myAmbient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mySpecular);
    glPushMatrix(); //Сохраняем VM=Fwe
    glRotatef(angle_light, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos_1);
    glEnable(GL_LIGHTING); // Включение расчета освещенности
    glEnable(GL_LIGHT0); // включаем этот конкретный источник
    glPopMatrix(); // Восстанавливаем VM=Fwe
    glPushMatrix(); //Сохраняем VM=Fwe
    glRotatef(angle, 0, 1, 0); // VM=Fwe*R
    glCallList(list);
    glPopMatrix(); // Восстанавливаем VM=Fwe
    glDisable(GL_LIGHTING); //Выключаем освещение
    glPopMatrix(); glutSwapBuffers();
    glEndList(); //Завершение накопления команд в списке
    Sleep(20);
}
void myReshape(int width, int height)
{
    float R = 640.0 / 480.0; //Форматное соотношение
    float w = 20; //Ширина мирового окна
    float h = w / R, l = -w / 2, r = w / 2, b = -h / 2, t = h / 2, n, f;
    if (width / height < 1) glViewport(0, 0, width, height);
    else glViewport(0, 0, width, height);
}
void myIdle()
{
    if (angle != 360) angle += angle_plus;
    else angle = 0;
    glutPostRedisplay();
}
void key_press(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'o': //нажате клавишы 0 - начало или конец вращение объёкта
        if (!check)
            angle_plus = 1;
        else
            angle_plus = 0;
        check = !check; break;
    case 'l': //нажате клавишы 1 - вращение источника света
        if (angle_light != 360) angle_light += 15;
        else angle_light = 0;
        break;
    case 'f': //нажате клавишы F - лицевый грани
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
        break;
    case 'b': //нажате клавишы B - нелицевый грани
        glCullFace(GL_FRONT);
        glEnable(GL_CULL_FACE);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void mouse_press(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    // устанавливает взаимодействие между текстурой и объектом - в данном случае текстурного отображения
        // GL_DECAL - аналог GL_REPLACE, но для RGB. - создаёт эффект светящегося объекта
    else if (button == GLUT_RIGHT_BUTTON)
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);// GL_MODULATE - модулирует коэффицент отражения для текстуры
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //устанавливая режим дисплея в функции main(), предусмотрено использование буфера глубины
        glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Lab 8 Gawish");
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(key_press);
    glutMouseFunc(mouse_press);
    glutReshapeFunc(myReshape);
    glutIdleFunc(myIdle);
    init();
    glutMainLoop();
}
void draw_K()
{
    float myDiffuse[] = { 0.55, 0.15, 0.008, 1 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw
    // параметры буквы К
    float k_1_left = -8.0,
        k_1_right = -6.5,
        k_2_right = -3.0, k_top = 8.5,
        k_bottom = 2.0,
        k_mid = (k_top + k_bottom) / 2;
    {//red
        glBegin(GL_POLYGON); //face
        glNormal3f(0, 0, 1);
        glVertex3f(k_1_left, k_bottom, thickness / 2);
        glVertex3f(k_1_right, k_bottom, thickness / 2);
        glVertex3f(k_1_right, k_top, thickness / 2);
        glVertex3f(k_1_left, k_top, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON); //back
        glNormal3f(0, 0, -1);
        glVertex3f(k_1_right, k_bottom, -thickness / 2);
        glVertex3f(k_1_left, k_bottom, -thickness / 2);
        glVertex3f(k_1_left, k_top, -thickness / 2);
        glVertex3f(k_1_right, k_top, -thickness / 2);
        glEnd();
        // left
        glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(k_1_left, k_bottom, -thickness / 2);
        glVertex3f(k_1_left, k_bottom, thickness / 2);
        glVertex3f(k_1_left, k_top, thickness / 2);
        glVertex3f(k_1_left, k_top, -thickness / 2);
        glEnd();
        // top part
        h1 = 2; h2 = k_top - k_mid; h3 = sqrt(h1 * h1 + h2 * h2);
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0); glVertex3f(k_1_left, k_top, thickness / 2);
        glVertex3f(k_1_right, k_top, thickness / 2);
        glVertex3f(k_1_right, k_top, -thickness / 2);
        glVertex3f(k_1_left, k_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glVertex3f(k_1_right, k_top, thickness / 2);
        glVertex3f(k_1_right, k_mid, thickness / 2);
        glVertex3f(k_1_right, k_mid, -thickness / 2);
        glVertex3f(k_1_right, k_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glVertex3f(k_1_right, k_mid, thickness / 2);
        glVertex3f(k_1_right, k_bottom, thickness / 2);
        glVertex3f(k_1_right, k_bottom, -thickness / 2);
        glVertex3f(k_1_right, k_mid, -thickness / 2);
        glEnd();
    }
    // FACE
    {
        float myDiffuse[] = { 0.15, 0.15, 0.2, 1 };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(k_1_right, k_mid, thickness / 2);
        glVertex3f(k_1_right + 1.7, k_mid, thickness / 2);
        glVertex3f(k_2_right, k_top, thickness / 2);
        glVertex3f(k_2_right - 1.7, k_top, thickness / 2); glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(k_2_right - 1.7, k_bottom, thickness / 2);
        glVertex3f(k_2_right, k_bottom, thickness / 2);
        glVertex3f(k_1_right + 1.7, k_mid, thickness / 2);
        glVertex3f(k_1_right, k_mid, thickness / 2);
        glEnd();
    }
    // BACK
    {
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(k_1_right + 1.7, k_mid, -thickness / 2);
        glVertex3f(k_1_right, k_mid, -thickness / 2);
        glVertex3f(k_2_right - 1.7, k_top, -thickness / 2);
        glVertex3f(k_2_right, k_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(k_2_right, k_bottom, -thickness / 2);
        glVertex3f(k_2_right - 1.7, k_bottom, -thickness / 2);
        glVertex3f(k_1_right, k_mid, -thickness / 2);
        glVertex3f(k_1_right + 1.7, k_mid, -thickness / 2);
        glEnd();
    }
    // BREDGES
    {
        glBegin(GL_POLYGON);
        glNormal3f(-h1 / h3, h2 / h3, 0);
        glVertex3f(k_1_right, k_mid, thickness / 2); glVertex3f(k_2_right - 1.7, k_top, thickness / 2);
        glVertex3f(k_2_right - 1.7, k_top, -thickness / 2);
        glVertex3f(k_1_right, k_mid, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(k_2_right - 1.7, k_top, thickness / 2);
        glVertex3f(k_2_right, k_top, thickness / 2);
        glVertex3f(k_2_right, k_top, -thickness / 2);
        glVertex3f(k_2_right - 1.7, k_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(h1 / h3, -h2 / h3, 0);
        glVertex3f(k_2_right, k_top, thickness / 2);
        glVertex3f(k_1_right + 1.7, k_mid, thickness / 2);
        glVertex3f(k_1_right + 1.7, k_mid, -thickness / 2);
        glVertex3f(k_2_right, k_top, -thickness / 2);
        glEnd();
        // bottom part
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(k_1_left, k_bottom, -thickness / 2);
        glVertex3f(k_1_right, k_bottom, -thickness / 2);
        glVertex3f(k_1_right, k_bottom, thickness / 2);
        glVertex3f(k_1_left, k_bottom, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(-h1 / h3, -h2 / h3, 0);
        glVertex3f(k_2_right - 1.7, k_bottom, thickness / 2);
        glVertex3f(k_1_right, k_mid, thickness / 2);
        glVertex3f(k_1_right, k_mid, -thickness / 2); glVertex3f(k_2_right - 1.7, k_bottom, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(k_2_right, k_bottom, thickness / 2);
        glVertex3f(k_2_right - 1.7, k_bottom, thickness / 2);
        glVertex3f(k_2_right - 1.7, k_bottom, -thickness / 2);
        glVertex3f(k_2_right, k_bottom, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(h1 / h3, h2 / h3, 0);
        glVertex3f(k_1_right + 1.7, k_mid, thickness / 2);
        glVertex3f(k_2_right, k_bottom, thickness / 2);
        glVertex3f(k_2_right, k_bottom, -thickness / 2);
        glVertex3f(k_1_right + 1.7, k_mid, -thickness / 2);
        glEnd();
    }
}
// параметры буквы T
void draw_T()
{
    float t_1_left = -2.0,
        t_1_right = 2.0,
        t_top = 8.5,
        t_bottom = 2.0,
        t_mid = -0.75;
    float myDiffuse[] = { 0.55, 0.15, 0.008, 1 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw// FACE
    {
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(t_1_left, t_top, thickness / 2);
        glVertex3f(t_1_right, t_top, thickness / 2);
        glVertex3f(t_1_right, t_top - 1.5, thickness / 2);
        glVertex3f(t_1_left, t_top - 1.5, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(t_mid, t_top - 1.5, thickness / 2);
        glVertex3f(t_mid, t_bottom, thickness / 2);
        glVertex3f(t_mid + 1.5, t_bottom, thickness / 2);
        glVertex3f(t_mid + 1.5, t_top - 1.5, thickness / 2);
        glEnd();
    }
    // BACK
    {
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(t_1_left, t_top, -thickness / 2);
        glVertex3f(t_1_right, t_top, -thickness / 2);
        glVertex3f(t_1_right, t_top - 1.5, -thickness / 2);
        glVertex3f(t_1_left, t_top - 1.5, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(t_mid, t_top - 1.5, -thickness / 2); glVertex3f(t_mid, t_bottom, -thickness / 2);
        glVertex3f(t_mid + 1.5, t_bottom, -thickness / 2);
        glVertex3f(t_mid + 1.5, t_top - 1.5, -thickness / 2);
        glEnd();
    }
    // BRIDGES
    {
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(t_1_left, t_top, -thickness / 2);
        glVertex3f(t_1_left, t_top - 1.5, -thickness / 2);
        glVertex3f(t_1_left, t_top - 1.5, thickness / 2);
        glVertex3f(t_1_left, t_top, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(t_1_right, t_top, -thickness / 2);
        glVertex3f(t_1_right, t_top - 1.5, -thickness / 2);
        glVertex3f(t_1_right, t_top - 1.5, thickness / 2);
        glVertex3f(t_1_right, t_top, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(t_mid, t_bottom, -thickness / 2);
        glVertex3f(t_mid, t_top - 1.5, -thickness / 2);
        glVertex3f(t_mid, t_top - 1.5, thickness / 2);
        glVertex3f(t_mid, t_bottom, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON); glNormal3f(0, 0, -1);
        glVertex3f(t_mid + 1.5, t_bottom, -thickness / 2);
        glVertex3f(t_mid + 1.5, t_top - 1.5, -thickness / 2);
        glVertex3f(t_mid + 1.5, t_top - 1.5, thickness / 2);
        glVertex3f(t_mid + 1.5, t_bottom, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(t_mid, t_top - 1.5, -thickness / 2);
        glVertex3f(t_mid, t_top - 1.5, thickness / 2);
        glVertex3f(t_1_left, t_top - 1.5, thickness / 2);
        glVertex3f(t_1_left, t_top - 1.5, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(t_mid + 1.5, t_top - 1.5, -thickness / 2);
        glVertex3f(t_mid + 1.5, t_top - 1.5, thickness / 2);
        glVertex3f(t_1_right, t_top - 1.5, thickness / 2);
        glVertex3f(t_1_right, t_top - 1.5, -thickness / 2);
        glEnd();
    }
}
void draw_Z()
{
    float myDiffuse[] = { 1, 1, 1, 1 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw
    float z_left = 3.0,
        z_right = 7.0,
        z_top = 8.5,
        z_bottom = 2.0; glBegin(GL_POLYGON); //передняя
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(z_left, z_bottom, thickness / 2);
    glTexCoord2f(0, 1); glVertex3f(z_left, z_top, thickness / 2);
    glTexCoord2f(1, 1); glVertex3f(z_right, z_top, thickness / 2);
    glTexCoord2f(1, 0); glVertex3f(z_right, z_bottom, thickness / 2);
    glEnd();
    glPixelZoom(1, -1);//переворачивается
    glBegin(GL_POLYGON); //задняя
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(z_left, z_bottom, -thickness / 2);
    glTexCoord2f(0, 1); glVertex3f(z_left, z_top, -thickness / 2);
    glTexCoord2f(1, 1); glVertex3f(z_right, z_top, -thickness / 2);
    glTexCoord2f(1, 0); glVertex3f(z_right, z_bottom, -thickness / 2);
    glEnd();
    glBegin(GL_POLYGON); //левая сторона
    glNormal3f(1, 0, 0);
    glVertex3f(z_left, z_top, thickness / 2);
    glVertex3f(z_left, z_bottom, thickness / 2);
    glVertex3f(z_left, z_bottom, -thickness / 2);
    glVertex3f(z_left, z_top, -thickness / 2);
    glEnd();
    glBegin(GL_POLYGON);//правная
    glNormal3f(-1, 0, 0);
    glVertex3f(z_right, z_top, thickness / 2); glVertex3f(z_right, z_bottom, thickness / 2);
    glVertex3f(z_right, z_bottom, -thickness / 2);
    glVertex3f(z_right, z_top, -thickness / 2);
    glEnd();
    glEndList();
}
void draw_I()
{
    float myDiffuse[] = { 0.15, 0.15, 0.2, 1 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // Источник света в CKw
    // параметры буквы И
    float i_1_left = 8.0,
        i_1_right = 9.5,
        i_2_left = 11.5,
        i_2_right = 13.0;
    float i_top = 8.5,
        i_bottom = 2.0;
    // FACE
    {
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(i_1_left, i_bottom, thickness / 2);
        glVertex3f(i_1_right, i_bottom, thickness / 2);
        glVertex3f(i_1_right, i_top, thickness / 2);
        glVertex3f(i_1_left, i_top, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1); glVertex3f(i_1_right, i_bottom, thickness / 2);
        glVertex3f(i_2_left, i_top - 3, thickness / 2);
        glVertex3f(i_2_left, i_top, thickness / 2);
        glVertex3f(i_1_right, i_bottom + 3, thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(i_2_left, i_bottom, thickness / 2);
        glVertex3f(i_2_right, i_bottom, thickness / 2);
        glVertex3f(i_2_right, i_top, thickness / 2);
        glVertex3f(i_2_left, i_top, thickness / 2);
        glEnd();
    }
    // BACK
    {
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(i_1_right, i_bottom, -thickness / 2);
        glVertex3f(i_1_left, i_bottom, -thickness / 2);
        glVertex3f(i_1_left, i_top, -thickness / 2);
        glVertex3f(i_1_right, i_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(i_2_left, i_top - 3, -thickness / 2);
        glVertex3f(i_1_right, i_bottom, -thickness / 2);
        glVertex3f(i_1_right, i_bottom + 3, -thickness / 2);
        glVertex3f(i_2_left, i_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(i_2_right, i_bottom, -thickness / 2); glVertex3f(i_2_left, i_bottom, -thickness / 2);
        glVertex3f(i_2_left, i_top, -thickness / 2);
        glVertex3f(i_2_right, i_top, -thickness / 2);
        glEnd();
    }
    // BRIDGES
    {
        glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(i_1_left, i_bottom, thickness / 2);
        glVertex3f(i_1_left, i_top, thickness / 2);
        glVertex3f(i_1_left, i_top, -thickness / 2);
        glVertex3f(i_1_left, i_bottom, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(i_1_left, i_top, thickness / 2);
        glVertex3f(i_1_right, i_top, thickness / 2);
        glVertex3f(i_1_right, i_top, -thickness / 2);
        glVertex3f(i_1_left, i_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glVertex3f(i_1_right, i_top, thickness / 2);
        glVertex3f(i_1_right, i_bottom, thickness / 2);
        glVertex3f(i_1_right, i_bottom, -thickness / 2);
        glVertex3f(i_1_right, i_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        h1 = -2; h2 = i_top - i_bottom - 2; h3 = sqrt(h1 * h1 + h2 * h2);
        glNormal3f(h1 / h3, h2 / h3, 0);
        glVertex3f(i_1_right, i_bottom + 3, thickness / 2); glVertex3f(i_2_left, i_top, thickness / 2);
        glVertex3f(i_2_left, i_top, -thickness / 2);
        glVertex3f(i_1_right, i_bottom + 3, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(i_2_left, i_top, thickness / 2);
        glVertex3f(i_2_right, i_top, thickness / 2);
        glVertex3f(i_2_right, i_top, -thickness / 2);
        glVertex3f(i_2_left, i_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glVertex3f(i_2_right, i_top, thickness / 2);
        glVertex3f(i_2_right, i_bottom, thickness / 2);
        glVertex3f(i_2_right, i_bottom, -thickness / 2);
        glVertex3f(i_2_right, i_top, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(i_2_right, i_bottom, thickness / 2);
        glVertex3f(i_2_left, i_bottom, thickness / 2);
        glVertex3f(i_2_left, i_bottom, -thickness / 2);
        glVertex3f(i_2_right, i_bottom, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(i_2_left, i_bottom, thickness / 2);
        glVertex3f(i_2_left, i_top, thickness / 2);
        glVertex3f(i_2_left, i_top, -thickness / 2);
        glVertex3f(i_2_left, i_bottom, -thickness / 2);
        glEnd(); glBegin(GL_POLYGON);
        glNormal3f(-h1 / h3, -h2 / h3, 0);
        glVertex3f(i_2_left, i_top - 3, thickness / 2);
        glVertex3f(i_1_right, i_bottom, thickness / 2);
        glVertex3f(i_1_right, i_bottom, -thickness / 2);
        glVertex3f(i_2_left, i_top - 3, -thickness / 2);
        glEnd();
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(i_1_right, i_bottom, thickness / 2);
        glVertex3f(i_1_left, i_bottom, thickness / 2);
        glVertex3f(i_1_left, i_bottom, -thickness / 2);
        glVertex3f(i_1_right, i_bottom, -thickness / 2);
        glEnd();
    }
}