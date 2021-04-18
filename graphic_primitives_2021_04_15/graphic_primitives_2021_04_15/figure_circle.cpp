#include "figure_circle.h"

void figure_circle::coordinates_calculate(void) {
	int radius_calculate = radius + 1;
	array_x_move[0] = array_x[0] = radius_calculate + rand() % (180 - radius_calculate);//height-20
	array_y_move[0] = array_y[0] = radius_calculate + rand() % (120 - radius_calculate);;//width-20

	for (int i = 0; i < quantity_of_point; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(quantity_of_point);

		float dx = radius * cosf(angle);
		float dy = radius * sinf(angle);
		if (i + 1 == quantity_of_point) {
			break;
		}
		else {
			array_x_move[i + 1] = array_x[i + 1] = array_x[0] + dx;
			array_y_move[i + 1] = array_y[i + 1] = array_y[0] + dy;
		}


	}
}

figure_circle::figure_circle(int* my_color, bool clar, bool paint) {
	for (int i = 0; i < 3; i++) {
		figure_color[i] = my_color[i];
	}
	figure_clarity = clar;
	initialization_array();
	figure_fill = paint;
}

figure_circle::figure_circle(void) {
	initialization_array();
	kind_of_figure = circle;
}


void figure_circle::figure_draw(void) {
	if (need_of_calculation) {
		coordinates_calculate();
		class_for_range::range_max_and_min_float(array_x_move, &max_x, &min_x, quantity_of_point);
		class_for_range::range_max_and_min_float(array_y_move, &max_y, &min_y, quantity_of_point);
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
			glEnable(GL_LINE_SMOOTH);//��� �����������, �� ��� �� ��������
			glBegin(GL_TRIANGLE_FAN);
			for (int i = 0; i < quantity_of_point; i++) {
				glVertex2d(array_x_move[i], array_y_move[i]);
			}
			glVertex2d(array_x_move[1], array_y_move[1]);
			glEnd();
			glDisable(GL_LINE_SMOOTH);//����������, ���� � ������ �� ����
		}
		else {
			glBegin(GL_LINE_LOOP);
			for (int i = 1; i < quantity_of_point; i++) {
				glVertex2d(array_x_move[i], array_y_move[i]);
			}
		}
		glEnd();
	}
	if (!figure_clarity) {
		glDisable(GL_BLEND);
	}
}

void figure_circle::figure_move(int x, int y) {
	class_for_range::move_max_min_float(array_x_move, &max_x, &min_x, quantity_of_point, x);
	class_for_range::move_max_min_float(array_y_move, &max_y, &min_y, quantity_of_point, y);
}

void figure_circle::crush_of_figure(void) {

}

void figure_circle::initialization_array(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x[i] = 0;
		array_y[i] = 0;
		array_x_move[i] = 0;
		array_y_move[i] = 0;
	}
}

void figure_circle::figure_position(int& x, int& y) {
		x = array_x_move[0];
		y = array_y_move[0];
}

void figure_circle::figure_position_for_track(int& x, int& y) {
	x = array_x_move[1];
	y = array_y_move[1];
}

void figure_circle::active_figure_paint(int num_color) {
	int byte = 16;
	for (int i = 0; i < 3; i++) {
		figure_color[i] = class_for_color::get_color(num_color) >> byte;
		byte -= 8;
	}
}

void figure_circle::active_figure_fill(int switch_fill) {
	if (switch_fill == 1) {
		figure_fill = false;
	}
	else {
		figure_fill = true;
	}
}

void figure_circle::active_figure_clarity(int switch_view) {
	if (switch_view == 3) {
		figure_clarity = false;
	}
	else if (switch_view == 2){
		figure_clarity = true;
	}
}

string figure_circle::get_parameters(void) {//������
	string str = "";
	str += to_string(kind_of_figure) + ";";
	str += to_string((int)round(array_x_move[0])) + ";";
	str += to_string((int)round(array_y_move[0])) + ";";
	str += to_string(figure::collect_color()) + ";";
	str += figure_clarity ? "1;" : "0;";
	str += figure_fill ? "1;" : "0;";
	return str;
}