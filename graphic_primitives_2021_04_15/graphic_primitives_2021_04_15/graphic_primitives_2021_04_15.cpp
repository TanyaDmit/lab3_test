// graphic_primitives_2021_04_15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <GL/freeglut.h>
#include <ctime>
#include "figure.h"
#include "figure_circle.h"
#include "figure_star.h"
#include "figure_triangle.h"
#include "figure_line.h"
#include "figure_square.h"
#include "class_for_color.h"
#include "figure_check_mark.h"

using namespace std;

const int width_Win = 1000;
const int height_Win = 700;
figure* arr_fig[10];

void reshape(int width, int height);
void general_draw(void);
void update(int value);

int main(int argc, char* argv[])
{
    cout << "Hello World!\n";

    // #1: Инициализация и создание окна GLUT
    glutInit(&argc, argv);//инициализация GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);//режим отображения информации
                                                 //GLUT_DOUBLE - вывод в окно с использованием 2 буферов
                                                 //GLUT_RGBA - RGB + прозрачность
    glutInitWindowPosition(50, 50);//отношение относительно верхнего левого угла экрана
    glutCreateWindow("HI!");//создание окна с заголовком
    glutInitWindowSize(height_Win, width_Win);//размеры окна
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);


    figure_circle circle_1;
    figure* point;
    point = &circle_1;
    arr_fig[0] = point;
    figure_circle circle_2;
    point = &circle_2;
    arr_fig[1] = point;
    int g[3] = { 123,17,45 };
    figure_star star_1(g, false, false);
    point = &star_1;
    arr_fig[2] = point;
    figure_triangle triangle_1;
    arr_fig[3] = &triangle_1;
    figure_line line_1;
    arr_fig[4] = &line_1;
    figure_square square_1;
    arr_fig[5] = &square_1;
    figure_check_mark m_1;
    arr_fig[6] = &m_1;
    // #2: Регистрация функций-обработчиков событий
    glutReshapeFunc(reshape);

    glutDisplayFunc(general_draw);// для рисования/перерисовки содержимого окна
    glutTimerFunc(1000, update, 0);
   
                       // #3: Запуск основного цикла GLUT
    glutMainLoop();
    return 1;
}

void reshape(int width, int height)
{

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    // Следующие действия производятся с матрицей проекции
    glLoadIdentity();//обнуление матрицы?
    glutReshapeWindow(width_Win, height_Win);
    gluOrtho2D(0, 200, 140, 0);
    glViewport(0, 0, width_Win, height_Win);
    glMatrixMode(GL_MODELVIEW);
    // Следующие действия производятся с матрицей модели

}

void general_draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//буфера цвета и глубины
    for (int i = 0; i < 7; i++) {
        arr_fig[i]->figure_draw();
    }
    glutSwapBuffers();
}

int i = 0, quantity = 5, x, y;

void update(int value) {
    //do your logic to change the cordinate of the enemy ships

    srand(time(0));
    if (i != quantity) {
        x = -5 + rand() % 5;
        y = -5 + rand() % 5;
        arr_fig[1]->figure_move(x, y);
        x = 1 + rand() % 7;
        y = 1 + rand() % 7;
        arr_fig[0]->figure_move(x, y);
        glutPostRedisplay();
        glutTimerFunc(1000, update, 0);
        i++;
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
