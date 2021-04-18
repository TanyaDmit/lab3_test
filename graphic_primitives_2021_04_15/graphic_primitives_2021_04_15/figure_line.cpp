#include "figure_line.h"

using namespace std;

void figure_line::coordinates_calculate(void) {
	array_x_move[1] = array_x[1] = array_x[0] + delta_x;
	array_y_move[1] = array_y[1] = array_y[0] + delta_y;
}

figure_line::figure_line(int x, int y, unsigned int my_color, bool clar, bool paint) {
	figure_color[2] = 0xff & my_color;
	figure_color[1] = 0xff & (my_color >> 8);
	figure_color[0] = 0xff & (my_color >> 16);
	figure_clarity = clar;
	figure_fill = paint;
	initialization_array();
	kind_of_figure = figure::line;
	array_x_move[0] = array_x[0] = x;
	array_y_move[0] = array_y[0] = y;
	need_of_calculation = true;
}

figure_line::figure_line(void) {
	initialization_array();
	kind_of_figure = figure::line;
	int delta_x_calculation = delta_x + 1, delta_y_calculation = delta_y + 1;
	array_x_move[0] = array_x[0] = delta_x_calculation + rand() % (180 - delta_x_calculation - delta_x);//height-20
	array_y_move[0] = array_y[0] = delta_y_calculation + rand() % (120 - delta_y_calculation - delta_y);//width-20
}

void figure_line::figure_draw(void) {
	if (need_of_calculation) {
		coordinates_calculate();
		class_for_range::range_max_and_min_int(array_x_move, &max_x, &min_x, quantity_of_point);
		class_for_range::range_max_and_min_int(array_y_move, &max_y, &min_y, quantity_of_point);
		need_of_calculation = false;
	}

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!figure_clarity) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	}
	else {
		glLineWidth(5);//������� �����
		if (!figure_crush) {
			glColor3ub(figure_color[0], figure_color[1], figure_color[2]);
			glBegin(GL_LINES);
			for (int i = 0; i < quantity_of_point; i++) {
				glVertex2d(array_x_move[i], array_y_move[i]);
			}
			glEnd();
		}
		else {
			glColor3ub(figure_color_crush[0], figure_color_crush[1], figure_color_crush[2]);
			glBegin(GL_LINES);
			for (int i = 0; i < quantity_of_point; i++) {
				glVertex2d(array_x_crush[i], array_y_crush[i]);
			}
			glEnd();
		}
		
	}
	if (!figure_clarity) {
		glDisable(GL_BLEND);
	}
	//glutSwapBuffers();
}

void figure_line::figure_move(int x, int y) {
	class_for_range::move_max_min_int(array_x_move, &max_x, &min_x, quantity_of_point, x);
	class_for_range::move_max_min_int(array_y_move, &max_y, &min_y, quantity_of_point, y);
}

void figure_line::crush_of_figure(void) {
	array_x_crush[0] = array_x_move[1];
	array_y_crush[0] = array_y_move[1];
	array_x_crush[1] = array_x_move[0] + delta_y;
	array_y_crush[1] = array_y_move[0] + delta_x;
}

void figure_line::control_crush(bool flag) {
	if (flag) {
		figure_crush = true;
		crush_of_figure();
	}
	else {
		figure_crush = false;
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
	for (int i = 0; i < quantity_of_point; i++) {
		x += array_x_move[i];
		y += array_y_move[i];
	}
	x = x / quantity_of_point;
	y = y / quantity_of_point;
}

void figure_line::figure_position_for_track(int& x, int& y) {
	x = array_x_move[1];
	y = array_y_move[1];
}

void figure_line::active_figure_paint(int num_color) {
	figure_color[2] = 0xff & class_for_color::get_selected_color(num_color);
	figure_color[1] = 0xff & (class_for_color::get_selected_color(num_color) >> 8);
	figure_color[0] = 0xff & (class_for_color::get_selected_color(num_color) >> 16);
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

string figure_line::get_parameters(void) {//������
	string str = "";
	str += to_string(kind_of_figure) + " ";
	str += to_string(array_x_move[0]) + " ";
	str += to_string(array_y_move[0]) + " ";
	str += to_string(figure::collect_color()) + " ";
	str += figure_clarity ? "1 " : "0 ";
	str += figure_fill ? "1 " : "0 ";
	return str;
}

void figure_line::return_to_start_position(void) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x_move[i] = array_x[i];
		array_y_move[i] = array_y[i];
	}
}