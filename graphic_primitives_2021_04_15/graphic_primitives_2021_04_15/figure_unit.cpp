#include "figure_unit.h"

using namespace std;

figure_unit::figure_unit(void) {
	for (int i = 0; i < quantity_of_object; i++) {
		arr_unit[i] = NULL;
	}
}

void figure_unit::add_figure(figure* target) {
	for (int i = 0; i < quantity_of_object; i++) {
		if (arr_unit[i] == NULL) {
			arr_unit[i] = target;
			return;
		}
	}
}

void figure_unit::figure_draw(void) {
	for (int i = 0; i < quantity_of_object; i++) {
		if (arr_unit[i] != NULL) {
			arr_unit[i]->figure_draw();
		}
	}
}

void figure_unit::figure_move(int x, int y) {
	for (int i = 0; i < quantity_of_object; i++) {
		if (arr_unit[i] != NULL) {
			arr_unit[i]->figure_move(x, y);
		}
	}
}

void figure_unit::figure_position(int& x, int& y) {
	bool check_quantity = false;
	for (int i = 1; i < quantity_of_object; i++) {
		if (arr_unit[i] == NULL) {
			arr_unit[i - 1]->figure_position(x, y);
			check_quantity = true;
			break;
		}
	}
	if (!check_quantity) {
		arr_unit[(quantity_of_object - 1)]->figure_position(x, y);
	}

}

void figure_unit::figure_position_for_track(int& x, int& y) {
	for (int i = 1; i < quantity_of_object; i++) {
		if (arr_unit[i] != NULL) {
			arr_unit[i]->figure_position_for_track(x, y);
		}
	}
}

void figure_unit::active_figure_paint(int) {

}