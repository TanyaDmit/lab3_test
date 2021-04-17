#include "figure_line.h"

using namespace std;

void figure_line::coordinates_calculate(void) {
	int delta_x_calculation = delta_x + 1, delta_y_calculation = delta_y + 1;
	array_x_move[0] = array_x[0] = delta_x_calculation + rand() % (180 - delta_x_calculation - delta_x);//height-20
	array_y_move[0] = array_y[0] = delta_y_calculation + rand() % (120 - delta_y_calculation - delta_y);//width-20
	array_x_move[1] = array_x[1] = array_x[0] + delta_x;
	array_y_move[1] = array_y[1] = array_y[0] + delta_y;
}

figure_line::figure_line(int* my_color, bool clar) {
	for (int i = 0; i < 3; i++) {
		figure_color[i] = my_color[i];
	}
	figure_clarity = clar;
	initialization_array();
	//kind_of_figure = line;//?
}

figure_line::figure_line(void) {
	initialization_array();
	kind_of_figure = line;
}

void figure_line::figure_draw(void) {
	if (need_of_calculation) {
		coordinates_calculate();
		need_of_calculation = false;
	}

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!figure_clarity) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	}
	else {
		glLineWidth(5);//толщина линии
		glColor3ub(figure_color[0], figure_color[1], figure_color[2]);

		glBegin(GL_LINES);
		for (int i = 0; i < quantity_of_point; i++) {
			glVertex2d(array_x_move[i], array_y_move[i]);
		}

		glEnd();
	}
	if (!figure_clarity) {
		glDisable(GL_BLEND);
	}
	//glutSwapBuffers();
}

void figure_line::figure_move(int x, int y) {
	int move = 1 + rand() % 10;
	for (int i = 0; i < quantity_of_point; i++) {
		array_x_move[i] += x;
		array_y_move[i] += y;
	}
}

void figure_line::initialization_array(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x[i] = 0;
		array_y[i] = 0;
		array_x_move[i] = 0;
		array_y_move[i] = 0;
	}
}

void figure_line::figure_position(int& x, int& y) {
	x = array_x_move[1];
	y = array_y_move[1];
}

void figure_line::active_figure_paint(int num_color) {
	int byte = 16;
	for (int i = 0; i < 3; i++) {
		figure_color[i] = class_for_color::get_color(num_color) >> byte;
		byte -= 8;
	}
}

void figure_line::active_figure_fill(int switch_fill) {
	if (switch_fill == 1) {
		cout << " Sorry, I can`t do this :( " << endl;
	}
	
}

void figure_line::active_figure_clarity(int switch_view) {
	if (switch_view == 3) {
		figure_clarity = false;
	}
	else if (switch_view == 2) {
		figure_clarity = true;
	}
}