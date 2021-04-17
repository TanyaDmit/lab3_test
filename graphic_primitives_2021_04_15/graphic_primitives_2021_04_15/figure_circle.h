#pragma once
#include "figure.h"
#include <math.h>

using namespace std;

class figure_circle : public figure {
private:
	static const int quantity_of_point = 55;
	float array_x[quantity_of_point];
	float array_y[quantity_of_point];
	float array_x_move[quantity_of_point];
	float array_y_move[quantity_of_point];
	float radius = 10;
	void coordinates_calculate(void);
	void initialization_array(void);
public:
	figure_circle(int*, bool, bool);
	figure_circle(void);
	void figure_draw(void);
	void figure_move(int, int);
	void figure_position(int&, int&);
	void active_figure_paint(int);
	void active_figure_fill(int);
	void active_figure_clarity(int);
};

