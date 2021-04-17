#pragma once
#include "figure.h"
#include <math.h>

class figure_star : public figure {
private:
	static const int quantity_of_point = 12;
	bool figure_fill;
	void coordinates_calculate(void);
	float array_x[quantity_of_point];
	float array_y[quantity_of_point];
	float array_x_move[quantity_of_point];
	float array_y_move[quantity_of_point];
	float radius = 10;
	float radius_small = 4;
	void initialization_array(void);
public:
	figure_star(int*, bool, bool);
	figure_star(void);
	void figure_draw(void);
	void figure_move(int, int);
	void figure_position(int&, int&);
};

