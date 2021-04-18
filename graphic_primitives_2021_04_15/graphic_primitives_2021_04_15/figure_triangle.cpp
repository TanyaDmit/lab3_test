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
	//kind_of_figure = triangle;//?
	figure_fill = paint;
}

figure_triangle::figure_triangle(void) {
	initialization_array();
	//kind_of_figure = triangle;
}

void figure_triangle::figure_draw(void) {
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
		if (!figure_crush) {
			glLineWidth(3);//������� �����
			glColor3ub(figure_color[0], figure_color[1], figure_color[2]);

			if (figure_fill) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < quantity_of_point; i++) {
				glVertex2d(array_x_move[i], array_y_move[i]);
			}
			glEnd();
		}
		else {
			glLineWidth(3);//������� �����
			glColor3ub(figure_color[0], figure_color[1], figure_color[2]);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			if (figure_fill) {
				glBegin(GL_TRIANGLE_FAN);
				for (int i = 0; i < (quantity_of_point +1); i++) {
					glVertex2d(array_x_crush[i], array_y_crush[i]);
				}
				glEnd();
			}
			else {
				glBegin(GL_LINE_LOOP);
				for (int i = 1; i < (quantity_of_point + 1); i++) {
					glVertex2d(array_x_crush[i], array_y_crush[i]);
				}
				glEnd();
			}
		}
		
	}
	if (!figure_clarity) {
		glDisable(GL_BLEND);
	}

	//glutSwapBuffers();
}

void figure_triangle::figure_move(int x, int y) {
	class_for_range::move_max_min_int(array_x_move, &max_x, &min_x, quantity_of_point, x);
	class_for_range::move_max_min_int(array_y_move, &max_y, &min_y, quantity_of_point, y);
}

void figure_triangle::crush_of_figure(void) {
	array_x_crush[0] = array_x_move[0];
	array_y_crush[0] = array_y_move[0];
	array_x_crush[1] = array_x_move[1];
	array_y_crush[1] = array_y_move[1];
	array_x_crush[2] = array_x_move[0];
	array_y_crush[2] = array_y_move[1];
	array_x_crush[3] = array_x_move[0]-delta_x/2;
	array_y_crush[3] = array_y_move[0]+delta_y/2;
}

void figure_triangle::control_crush(bool flag) {
	if (flag) {
		figure_crush = true;
		crush_of_figure();
	}
	else {
		figure_crush = false;
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
	for (int i = 0; i < quantity_of_point; i++) {
		x += array_x_move[i];
		y += array_y_move[i];
	}
	x = x / quantity_of_point;
	y = y / quantity_of_point;
}

void figure_triangle::figure_position_for_track(int& x, int& y) {
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
	if (switch_fill == 1) {
		figure_fill = false;
	}
	else {
		figure_fill = true;
	}
}

void figure_triangle::active_figure_clarity(int switch_view) {
	if (switch_view == 3) {
		figure_clarity = false;
	}
	else if (switch_view == 2) {
		figure_clarity = true;
	}
}