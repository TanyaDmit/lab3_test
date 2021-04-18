#include "figure_unit.h"

figure_unit::figure_unit(void) {
	for (int i = 0; i < quantity_of_object; i++) {
		arr_unit[i] = NULL;
	}
}

void figure_unit::add_figure(figure* target) {
	for (int i = 0; i < quantity_of_object; i++) {
		if (arr_unit[i] == NULL) {
			arr_unit[i] = target;
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