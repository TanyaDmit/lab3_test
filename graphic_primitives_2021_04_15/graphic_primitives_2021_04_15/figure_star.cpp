#include "figure_star.h"

using namespace std;

void figure_star::coordinates_calculate(void) {
	int radius_calculate = radius + 1;
	array_x_move[0] = array_x[0] = radius_calculate + rand() % (180 - radius_calculate);//height-20
	array_y_move[0] = array_y[0] = radius_calculate + rand() % (120 - radius_calculate);//width-20
	float angle_of_rotation = 1.257;
	float bias = 0.5;
	float x_center = array_x_move[0], y_center = array_y_move[0];
	const float step = float(3.1415926 * 2 / 5);//���� ����� �������� ���������
	float angle_interior = float(3.1415926 * 3 / 2 + angle_of_rotation);//�������
	float angle_external = float(3.1415926 * 3 / 2 + angle_of_rotation + bias);//�������
	for (int i = 1; i < quantity_of_point; i++) {
		if (i % 2 != 0) {
			array_x_move[i] = array_x[i] = x_center + radius_small * cosf(angle_interior);
			array_y_move[i] = array_y[i] = y_center + radius_small * sinf(angle_interior);
			angle_interior += step;
		}
		else {
			array_x_move[i] = array_x[i] = x_center + radius * cosf(angle_external);
			array_y_move[i] = array_y[i] = y_center + radius * sinf(angle_external);
			angle_external += step;
		}
	}
}

figure_star::figure_star(int* my_color, bool clar, bool paint) {
	for (int i = 0; i < 3; i++) {
		figure_color[i] = my_color[i];
	}
	figure_clarity = clar;
	initialization_array();
	kind_of_figure = star;
	//kind_of_figure = my_type;//? � �� ������� ����� ������, ����� ��� �������� ���
	figure_fill = paint;
}

figure_star::figure_star(void) {
	initialization_array();
	kind_of_figure = star;
}


void figure_star::figure_draw(void) {
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
		glLineWidth(3);//������� �����
		glColor3ub(figure_color[0], figure_color[1], figure_color[2]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (figure_fill) {
			glBegin(GL_TRIANGLE_FAN);
			for (int i = 0; i < quantity_of_point; i++) {
				glVertex2d(array_x_move[i], array_y_move[i]);
			}
			glEnd();
		}
		else {
			glBegin(GL_LINE_LOOP);
			for (int i = 1; i < quantity_of_point; i++) {
				glVertex2d(array_x[i], array_y[i]);
			}
			glEnd();
		}
	}
	if (!figure_clarity) {
		glDisable(GL_BLEND);
	}
	//glutSwapBuffers();
}

void figure_star::figure_move(int x, int y) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x_move[i] += x;
		array_y_move[i] += y;
	}
}

void figure_star::initialization_array(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x[i] = 0;
		array_y[i] = 0;
		array_x_move[i] = 0;
		array_y_move[i] = 0;
	}
}

void figure_star::figure_position(int& x, int& y) {
		x = array_x_move[0];
		y = array_y_move[0];
}

void figure_star::active_figure_paint(int num_color) {
	int byte = 16;
	for (int i = 0; i < 3; i++) {
		figure_color[i] = class_for_color::get_color(num_color) >> byte;
		byte -= 8;
	}
}

void figure_star::active_figure_fill(int switch_fill) {
	if (switch_fill == 1) {
		figure_fill = false;
	}
	else {
		figure_fill = true;
	}
}

void figure_star::active_figure_clarity(int switch_view) {
	if (switch_view == 3) {
		figure_clarity = false;
	}
	else if (switch_view == 2) {
		figure_clarity = true;
	}
}