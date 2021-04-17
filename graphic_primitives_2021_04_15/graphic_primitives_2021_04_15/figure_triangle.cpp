#include "figure_triangle.h"

void figure_triangle::coordinates_calculate(void) {
	int delta_x_calculation = delta_x + 1, delta_y_calculation = delta_y + 1;
	array_x_move[0] = array_x[0] = delta_x_calculation + rand() % (180 - delta_x_calculation);//height-20
	array_y_move[0] = array_y[0] = delta_y_calculation + rand() % (120 - delta_y_calculation);//width-20
	array_x_move[1] = array_x[1] = array_x[0] + delta_x;
	array_x_move[2] = array_x[2] = array_x[0] - delta_x;
	array_y_move[1] = array_y[1] = array_y[0] + delta_y;
	array_y_move[2] = array_y[2] = array_y[1];
}

figure_triangle::figure_triangle(int* my_color, bool clar, bool paint) {
	for (int i = 0; i < 3; i++) {
		figure_color[i] = my_color[i];
	}
	figure_clarity = clar;
	initialization_array();
	kind_of_figure = triangle;//?
	figure_fill = paint;
}

figure_triangle::figure_triangle(void) {
	initialization_array();
	kind_of_figure = triangle;
}

void figure_triangle::figure_draw(void) {
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
		glLineWidth(3);//толщина линии
		glColor3ub(figure_color[0], figure_color[1], figure_color[2]);

		if (figure_fill) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < quantity_of_point; i++) {
			glVertex2d(array_x[i], array_y[i]);
		}
		glEnd();
	}
	if (!figure_clarity) {
		glDisable(GL_BLEND);
	}

	//glutSwapBuffers();
}

void figure_triangle::figure_move(int x, int y) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x_move[i] += x;
		array_y_move[i] += y;
	}
}

void figure_triangle::initialization_array(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x[i] = 0;
		array_y[i] = 0;
		array_x_move[i] = 0;
		array_y_move[i] = 0;
	}
}

void figure_triangle::figure_position(int& x, int& y) {
	x = array_x_move[1];
	y = array_y_move[1];
}

void figure_triangle::active_figure_paint(int num_color) {
	int byte = 16;
	for (int i = 0; i < 3; i++) {
		figure_color[i] = class_for_color::get_color(num_color) >> byte;
		byte -= 8;
	}
}

void figure_triangle::active_figure_fill(int switch_fill) {
	if (switch_fill % 2 == 0) {
		figure_fill = true;
	}
	else {
		figure_fill = false;
	}
}

void figure_triangle::active_figure_clarity(int switch_fill) {
	if (switch_fill % 2 == 0) {
		figure_clarity = true;
	}
	else {
		figure_clarity = false;
	}
}