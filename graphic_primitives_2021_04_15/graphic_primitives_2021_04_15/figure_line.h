#pragma once
#include "figure.h"
class figure_line : public figure {
private:
	static const int quantity_of_point = 2;
	
	int array_x[quantity_of_point];
	int array_y[quantity_of_point];
	int array_x_move[quantity_of_point];
	int array_y_move[quantity_of_point];
	int delta_x = 10, delta_y = 20;
	void initialization_array(void);
	void coordinates_calculate(void);
public:
	figure_line(int*, bool);
	figure_line(void);
	void figure_draw(void);
	void figure_move(int, int);
	void figure_position(int&, int&);
	void active_figure_paint(int);
};

