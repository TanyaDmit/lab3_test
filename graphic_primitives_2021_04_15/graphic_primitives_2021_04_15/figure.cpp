#include "figure.h"

using namespace std;

void figure::figure_move(int x, int y) {}

void figure::figure_draw(void) {}

void figure::coordinates_calculate(void) {}

void figure::initialization_array(void){}

figure::figure(void) {//��������� �������� �� 0 �� 30 
	                  //��� ��� ������ ������� ������� �������� ������ �� �������� �������
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