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

figure_circle::figure_circle(int* my_color, bool clar, bool paint, kind_of_figure_t my_type) {
	for (int i = 0; i < 3; i++) {
		figure_color[i] = my_color[i];
	}
	figure_clarity = clar;
	initialization_array();
	kind_of_figure = my_type;
	figure_fill = paint;
}

figure_circle::figure_circle(void) {

	initialization_array();
	kind_of_figure = circle;
}


void figure_circle::figure_draw(void) {
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

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (figure_fill) {
			glEnable(GL_LINE_SMOOTH);//для сглаживания, но оно не работает
			glBegin(GL_TRIANGLE_FAN);
			cout << " tyt fill" << endl;
			for (int i = 0; i < quantity_of_point; i++) {
				glVertex2d(array_x_move[i], array_y_move[i]);
			}
			glVertex2d(array_x_move[1], array_y_move[1]);
			glEnd();
			glDisable(GL_LINE_SMOOTH);//аналогично, либо я просто не вижу
		}
		else {
			glBegin(GL_LINE_LOOP);
			cout << " tyt line " << endl;
			for (int i = 1; i < quantity_of_point; i++) {
				glVertex2d(array_x_move[i], array_y_move[i]);
			}
		}
		glEnd();
		if (!figure_clarity) {
			glDisable(GL_BLEND);
		}
	}
}

void figure_circle::figure_move(int x, int y) {
	for (int i = 0; i < quantity_of_point; i++) {
		array_x_move[i] += x;
		array_y_move[i] += y;
	}
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
	if (switch_fill % 2 == 0) {
		figure_fill = true;
	}
	else {
		figure_fill = false;
	}
}

void figure_circle::active_figure_clarity(int switch_fill) {
	if (switch_fill % 2 == 0) {
		figure_clarity = true;
	}
	else {
		figure_clarity = false;
	}
}