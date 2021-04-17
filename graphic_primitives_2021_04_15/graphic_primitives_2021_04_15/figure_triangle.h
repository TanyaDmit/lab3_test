#pragma once
#include "figure.h"

class figure_triangle : public figure {
private:
	static const int quantity_of_point = 3;
	void coordinates_calculate(void);
	int array_x[quantity_of_point];
	int array_y[quantity_of_point];
	int array_x_move[quantity_of_point];
	int array_y_move[quantity_of_point];
	int delta_x = 10, delta_y = 20;
public:
	figure_triangle(int*, bool, bool);
	figure_triangle(void);
	void figure_draw(void);
	void figure_move(int, int);
	void initialization_array(void);
	void figure_position(int&, int&);
	void active_figure_paint(int);
};

