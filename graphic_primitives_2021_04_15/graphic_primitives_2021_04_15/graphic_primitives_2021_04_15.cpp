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

int selector_figure_from_keyboard = -1;//для мерцания и галочки
int selector_figure_active_now = 0;//для мерцания и галочки


int number_first_empty = 0;
figure* arr_fig[figure::general_quantity_of_figure];

//для библиотеки
void reshape(int width, int height);
void general_draw(void);
void keyboard(unsigned char key, int x, int y);

//для таймеров
void update(int value);
void select(int value);
//void clarity(int value);

//
void search_number_first_empty(void);
int search_number_first_filled(int start);

//для меню
int type_of_figure, color_of_figure, fill_of_figure, clarity_of_figure, call_of_figure;
bool menuFlag;
void type_of_figure_func(int value);
void color_of_figure_func(int value);
void fill_of_figure_func(int value);
void clarity_of_figure_func(int value);
void call_of_figure_func(int value) {};
void process_menu_status(int status, int x, int y);
void create_figure_main_menu(void);
enum { select_circle = 1, select_line, select_star, select_triangle, select_square };
enum {
    select_light_green = 1, select_pink, select_lilac, select_dark_blue, select_turquoise,
    select_dark_green, select_light_blue, select_purple, select_yellow, select_swampy
};
enum { select_fill, select_empty, select_view, select_hidden };




int main(int argc, char* argv[])
{
    cout << "Hello World!\n";
    for (int i = 0; i < figure::general_quantity_of_figure; i++) {
        arr_fig[i] = NULL;
    }
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


    figure_check_mark m_1;
    
    figure* point;
    point = &m_1;
    arr_fig[9] = point;
    figure_circle circle_2;
    point = &circle_2;
    arr_fig[1] = point;
    figure_star star_1;
    point = &star_1;
    arr_fig[2] = point;
    figure_triangle triangle_1;
    arr_fig[3] = &triangle_1;
    figure_line line_1;
    arr_fig[4] = &line_1;
    figure_square square_1;
    arr_fig[5] = &square_1;
    figure_circle circle_1;
    arr_fig[6] = &circle_1;
    // #2: Регистрация функций-обработчиков событий
    glutReshapeFunc(reshape);

    glutDisplayFunc(general_draw);// для рисования/перерисовки содержимого окна
    glutTimerFunc(1000, update, 0);
    glutTimerFunc(100, select, 0);
    glutKeyboardFunc(keyboard);

    // инициализация меню
    create_figure_main_menu();

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
    for (int i = 0; i < figure::general_quantity_of_figure; i++) {
        if (arr_fig[i] != NULL) {
            arr_fig[i]->figure_draw();
        }
    }
    glutSwapBuffers();
}

int i = 0, quantity = 5, x, y;

void update(int value) {
   /* //do your logic to change the cordinate of the enemy ships

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
    */
}
void select(int value) {//вызов видимости

    selector_figure_active_now = search_number_first_filled(selector_figure_active_now);
    if ((selector_figure_active_now >= 0) && (selector_figure_active_now == selector_figure_from_keyboard)) {
        //arr_fig[selector]->my_clarity(false);
        int x_p = 0, y_p = 0;
        arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);//выбранный
        cout << x_p << " " << y_p << endl;
        arr_fig[(figure::general_quantity_of_figure - 1)]->figure_move(x_p, y_p);
    }
    else {//галочку надо спрятать и по умолчанию она спрятана

    }

    glutPostRedisplay();
    glutTimerFunc(100, select, 0);

}
void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) exit(0); // 27 - код клавиши Esc
    if (key == 'A') {
        selector_figure_from_keyboard = search_number_first_filled(selector_figure_from_keyboard);
    }
}

void search_number_first_empty(void) {
    for (int i = 0; i < (figure::general_quantity_of_figure-1); i++) {
        if (arr_fig[i] == NULL) {
            number_first_empty = i;
            return;
        }
    }
    number_first_empty = -1;
}

int search_number_first_filled(int start) {

    for (int i = 1; i < (figure::general_quantity_of_figure-1); i++) {
        start++;
        if (start >= (figure::general_quantity_of_figure-1)) {
            start = 0;
        }
        if (arr_fig[start] != NULL) {
            return start;
        }
    }
    return -1;
}


//menu
void processMenuStatus(int status, int x, int y) {
    if (status == GLUT_MENU_IN_USE)
        menuFlag = true;
    else
        menuFlag = false;
}

void create_figure_main_menu(void) {
    type_of_figure = glutCreateMenu(type_of_figure_func);
    glutAddMenuEntry("   circle  ", select_circle);
    glutAddMenuEntry(" line ", select_line);
    glutAddMenuEntry("   star  ", select_star);
    glutAddMenuEntry(" triangle ", select_triangle);
    glutAddMenuEntry(" square ", select_square);
    color_of_figure = glutCreateMenu(color_of_figure_func);
    glutAddMenuEntry("    light_green     ", select_light_green);
    glutAddMenuEntry("    pink     ", select_pink);
    glutAddMenuEntry("    lilac     ", select_lilac);
    glutAddMenuEntry("   dark_blue  ", select_dark_blue);
    glutAddMenuEntry("   turquoise   ", select_turquoise);
    glutAddMenuEntry("   dark_green   ", select_dark_green);
    glutAddMenuEntry("  light_blue   ", select_light_blue);
    glutAddMenuEntry("   purple     ", select_purple);
    glutAddMenuEntry("    yellow     ", select_yellow);
    glutAddMenuEntry("    swampy     ", select_swampy);
    fill_of_figure = glutCreateMenu(fill_of_figure_func);
    glutAddMenuEntry("    fill     ", select_fill);
    glutAddMenuEntry("    empty    ", select_empty);
    clarity_of_figure = glutCreateMenu(clarity_of_figure_func);
    glutAddMenuEntry("    view     ", select_view);
    glutAddMenuEntry("    hidden    ", select_hidden);
    call_of_figure = glutCreateMenu(call_of_figure_func);
    glutAddSubMenu("  create object ", type_of_figure);
    glutAddSubMenu("     color     ", color_of_figure);
    glutAddSubMenu("     fill     ", fill_of_figure);
    glutAddSubMenu("     clarity     ", clarity_of_figure);
    // прикрепить меню к правой кнопке
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //статус активности меню
    glutMenuStatusFunc(processMenuStatus);
}

void type_of_figure_func(int value) {
    search_number_first_empty();
    if (number_first_empty >= 0) {
        switch (value) {
        case select_circle: {
            figure_circle tmp;
            arr_fig[number_first_empty] = &tmp;
            cout << " i am " << number_first_empty << endl;
            break;
        }


        case select_line: {

            figure_line tmp;
            arr_fig[number_first_empty] = &tmp;
            break;
        }
        case select_star: {
            figure_star tmp;
            arr_fig[number_first_empty] = &tmp;
            break;
        }


        case select_triangle: {
            figure_triangle tmp;
            arr_fig[number_first_empty] = &tmp;
            break;
        }

        case select_square: {
            figure_square tmp;
            arr_fig[number_first_empty] = &tmp;
            break;
        }
        default:
            cout << "live is pain" << endl;
            break;
        }
    }
    else {
        cout << " game over :) " << endl;
    }

}

void color_of_figure_func(int value) {
    switch (value) {
    case select_light_green:
        cout << "buttom 2.1 - is good" << endl;
        break;

    case select_pink:
        cout << "buttom 2.2 - is good" << endl;
        break;
    case select_lilac:
        cout << "buttom 2.1 - is good" << endl;
        break;
    case select_dark_blue:
        cout << "buttom 2.1 - is good" << endl;
        break;

    case select_turquoise:
        cout << "buttom 2.2 - is good" << endl;
        break;
    case select_dark_green:
        cout << "buttom 2.1 - is good" << endl;
        break;

    case select_light_blue:
        cout << "buttom 2.2 - is good" << endl;
        break;
    case select_purple:
        cout << "buttom 2.1 - is good" << endl;
        break;

    case select_yellow:
        cout << "buttom 2.2 - is good" << endl;
        break;

    case select_swampy:
        cout << "buttom 2.2 - is good" << endl;
        break;
    default:
        cout << "static live is pain" << endl;
        break;
    }
}

void fill_of_figure_func(int value) {
    switch (value) {
    case select_fill:
        cout << "buttom 2.2 - is good" << endl;
        break;

    case select_empty:
        cout << "buttom 2.2 - is good" << endl;
        break;
    default:
        cout << "static live is pain" << endl;
        break;

    }
}

void clarity_of_figure_func(int value) {
    switch (value) {
    case select_view:
        cout << "buttom 2.2 - is good" << endl;
        break;

    case select_hidden:
        cout << "buttom 2.2 - is good" << endl;
        break;
    default:
        cout << "static live is pain" << endl;
        break;

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
