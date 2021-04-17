#pragma once
#include "figure.h"
class figure_square : public figure {
private:
	static const int quantity_of_point = 4;
	int array_x[quantity_of_point];
	int array_y[quantity_of_point];
	int array_x_move[quantity_of_point];
	int array_y_move[quantity_of_point];
	int delta_x = 15, delta_y = 15;
	void initialization_array(void);
	void coordinates_calculate(void);
public:
	figure_square(int*, bool, bool);
	figure_square(void);
	void figure_draw(void);
	void figure_move(int, int);
	void figure_position(int&, int&);
	void active_figure_paint(int);
	void active_figure_fill(int);
};

