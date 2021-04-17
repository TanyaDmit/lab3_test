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
#include "figure_point.h"

using namespace std;

const int width_Win = 1000;
const int height_Win = 700;

int selector_figure_from_keyboard = -1;//для мерцания и галочки
int selector_figure_active_now = 0;//для мерцания и галочки активная фигура
int counter_for_move = 0, max_quantity_move = 7, x, y;//для движения

int number_first_empty = 0;
figure* arr_fig[figure::general_quantity_of_figure];

//для библиотеки
void reshape(int width, int height);
void general_draw(void);
void keyboard(unsigned char key, int x, int y);
void special_key(int s_key, int y, int z);

//для таймеров
void move_without_track(int value);
void move_with_track(int value);
void select(int value);
//void clarity(int value);

//
void search_number_first_empty(void);
int search_number_first_filled(int start);
void start_filled_figure(void);

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
	select_light_green = 0, select_pink, select_lilac, select_dark_blue, select_turquoise,
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
	{
		arr_fig[9] = new figure_check_mark;
		arr_fig[8] = new figure_point;
		arr_fig[1] = new figure_circle;
		arr_fig[2] = new figure_star;
		arr_fig[3] = new figure_triangle;
		arr_fig[4] = new figure_star;
		arr_fig[5] = new figure_square;
		arr_fig[6] = new figure_circle;
	}
	start_filled_figure();
	// #2: Регистрация функций-обработчиков событий
	glutReshapeFunc(reshape);

	glutDisplayFunc(general_draw);// для рисования/перерисовки содержимого окна
	//glutTimerFunc(1000, update, 0);

	//glutTimerFunc(100, select, 0);
	glutSpecialFunc(special_key);
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
	glFlush();
	glutSwapBuffers();
}

void move_without_track(int value) {
	
	 if (counter_for_move != max_quantity_move) {
		 x = -5 + rand() % 5;
		 y = -2 + rand() % 5;
		 arr_fig[selector_figure_active_now]->figure_move(x, y);
		 int x_p = 0, y_p = 0;
		 arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);
		 x += x_p;
		 y += y_p;
		 arr_fig[(figure::general_quantity_of_figure - 1)]->figure_move(x, y);
		 glutPostRedisplay();
		 glutTimerFunc(1000, move_without_track, 0);
		 counter_for_move++;
	 }
	 
}

void move_with_track(int value) {
	if (counter_for_move != max_quantity_move) {
		x = -5 + rand() % 5;
		y = -2 + rand() % 5;
		arr_fig[selector_figure_active_now]->figure_move(x, y);
		int x_p = 0, y_p = 0; 
		int x_p_for_track = 0, y_p_for_track = 0;
		arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);
		arr_fig[selector_figure_active_now]->figure_position_for_track(x_p_for_track, y_p_for_track);
		x += x_p;
		y += y_p;
		arr_fig[(figure::general_quantity_of_figure - 1)]->figure_move(x, y);		
		arr_fig[(figure::general_quantity_of_figure - 2)]->figure_move(x_p_for_track, y_p_for_track);
		glutPostRedisplay();
		glutTimerFunc(1000, move_with_track, 0);
		counter_for_move++;
	}
}

void special_key(int s_key, int y, int z){
	switch (s_key) {
	case GLUT_KEY_F2:
		counter_for_move = 0;
		glutTimerFunc(1000, move_without_track, 0);
		break;
	case GLUT_KEY_F3:
		counter_for_move = 0;
		glutTimerFunc(1000, move_with_track, 0);
		break;
	}

}

void select(int value) {//вызов видимости
	/*
	* selector_figure_active_now = search_number_first_filled(selector_figure_active_now);
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
	*/

}
void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0); // 27 - код клавиши Esc
	if (key == ' ') {
		selector_figure_from_keyboard = search_number_first_filled(selector_figure_from_keyboard);
		selector_figure_active_now = search_number_first_filled(selector_figure_active_now);
		if ((selector_figure_active_now >= 0) && (selector_figure_active_now == selector_figure_from_keyboard)) {
			//arr_fig[selector]->my_clarity(false);
			int x_p = 0, y_p = 0;
			arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);//выбранный
			arr_fig[(figure::general_quantity_of_figure - 1)]->figure_move(x_p, y_p);
		}
		else {//галочку надо спрятать и по умолчанию она спрятана

		}

		glutPostRedisplay();
	}
}

void search_number_first_empty(void) {
	for (int i = 0; i < (figure::general_quantity_of_figure - 2); i++) {
		if (arr_fig[i] == NULL) {
			number_first_empty = i;
			return;
		}
	}
	number_first_empty = -1;
}

int search_number_first_filled(int start) {

	for (int i = 0; i < (figure::general_quantity_of_figure - 2); i++) {
		start++;
		if (start >= (figure::general_quantity_of_figure - 2)) {
			start = 0;
		}
		if (arr_fig[start] != NULL) {
			return start;
		}
	}
	return -1;
}

void start_filled_figure(void) {
	for (int i = 0; i < (figure::general_quantity_of_figure - 1); i++) {
		if (arr_fig[i] != NULL) {
			selector_figure_active_now = i;
		}
	}
	if (selector_figure_active_now >= 0) {
		//arr_fig[selector]->my_clarity(false);
		int x_p =0, y_p=0 ;
		arr_fig[selector_figure_active_now]->figure_position(x_p, y_p);//выбранный
		arr_fig[(figure::general_quantity_of_figure - 1)]->figure_move(x_p, y_p);
	}
	glutPostRedisplay();
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
		case select_circle:
			arr_fig[number_first_empty] = new figure_circle;
			break;

		case select_line:
			arr_fig[number_first_empty] = new figure_line;
			break;

		case select_star:
			arr_fig[number_first_empty] = new figure_star;
			break;

		case select_triangle:
			arr_fig[number_first_empty] = new figure_triangle;
			break;

		case select_square:
			arr_fig[number_first_empty] = new figure_square;
			break;

		default:
			cout << "live is pain" << endl;
			break;
		}
		glFlush();
		glutPostRedisplay();
	}
	else {
		cout << " game over :) " << endl;
	}

}

void color_of_figure_func(int value) {
	switch (value) {
	case select_light_green:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_light_green);
		break;

	case select_pink:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_pink);
		break;
	case select_lilac:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_lilac);
		break;
	case select_dark_blue:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_dark_blue);
		break;

	case select_turquoise:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_turquoise);
		break;
	case select_dark_green:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_dark_green);
		break;

	case select_light_blue:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_light_blue);
		break;
	case select_purple:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_purple);
		break;

	case select_yellow:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_yellow);
		break;

	case select_swampy:
		arr_fig[selector_figure_active_now]->active_figure_paint(select_swampy);
		break;
	default:
		cout << "static live is pain" << endl;
		break;
	}

	glFlush();
	glutPostRedisplay();
}

void fill_of_figure_func(int value) {
	switch (value) {
	case select_fill:
		arr_fig[selector_figure_active_now]->active_figure_fill(select_fill);
		break;

	case select_empty:
		arr_fig[selector_figure_active_now]->active_figure_fill(select_empty);
		break;
	default:
		cout << "static live is pain" << endl;
		break;
	}
	glFlush();
	glutPostRedisplay();
}

void clarity_of_figure_func(int value) {
	switch (value) {
	case select_view:
		arr_fig[selector_figure_active_now]->active_figure_clarity(select_view);
		break;

	case select_hidden:
		arr_fig[selector_figure_active_now]->active_figure_clarity(select_hidden);
		break;
	default:
		cout << "static live is pain" << endl;
		break;
	}
	glFlush();
	glutPostRedisplay();
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
