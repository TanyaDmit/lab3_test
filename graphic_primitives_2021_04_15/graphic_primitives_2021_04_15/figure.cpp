#include "figure.h"

using namespace std;

static int my_number = 0;

void figure::figure_move(int x, int y) {}

void figure::figure_draw(void) {}

void figure::coordinates_calculate(void) {}

void figure::initialization_array(void){}

void figure::figure_position(int&, int&) {}

void figure::figure_position_for_track(int&, int&) {}

void figure::active_figure_paint(int) {}

void figure::active_figure_fill(int) {}

void figure::active_figure_clarity(int) {}

figure::figure(void) {
	int byte = 16;
	my_number++;
	for (int i = 0; i < 3; i++) {
		figure_color[i] = class_for_color::get_color(my_number) >> byte;
		byte -= 8;
	}
	figure_clarity = true;
	need_of_calculation = true;
	need_to_select = false;
	figure_fill = true;
}

void figure::activ_selected(bool choise) {
	if (choise) {
		need_to_select = true;
	}
	else {
		need_to_select = false;
	}
}

void figure::get_max_min(int* arr_max_min) {
	arr_max_min[0] = max_x;
	arr_max_min[1] = max_y;
	arr_max_min[2] = min_x;
	arr_max_min[3] = min_y;
	for (int i = 0; i < 4; i++) {
		cout << arr_max_min[i] << " ";
	}
	cout << endl;
}
