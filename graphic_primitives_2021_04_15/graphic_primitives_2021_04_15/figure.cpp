#include "figure.h"

using namespace std;

void figure::figure_move(int x, int y) {}

void figure::figure_draw(void) {}

void figure::coordinates_calculate(void) {}

void figure::initialization_array(void){}

figure::figure(void) {//исключила варианты от 0 до 30 
	                  //так как чистый зеленый должены выпадать только на активном объекте
	figure_clarity = false;
	for (int i = 0; i < 3; i++) {
		figure_color[i] =i + rand() % RGB_max;//+30
	}
}

void figure::activ_selected(bool choise) {
	if (choise) {
		need_to_select = true;
	}
}