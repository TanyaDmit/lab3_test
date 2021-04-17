#include "class_for_color.h"

using namespace std;

enum type_of_color_t {
	light_green = 4325120, pink = 16711889, lilac = 11796637, dark_blue = 102,
	turquoise = 65535, dark_green = 39458, light_blue = 4430591,
	purple = 7864477, yellow = 16776960, swampy = 10131968
};

static int how_many = 0;

static int opportunity_color[] = { light_green, pink, lilac, dark_blue,
						  turquoise, dark_green,  light_blue,
						  purple, yellow, swampy };

const int quantity = sizeof(opportunity_color) / sizeof(type_of_color_t);

int class_for_color::get_color(int index) {
	return (int)opportunity_color[index % quantity];
}

void class_for_color::out_all(void)
{
	for (int i = 0; i < quantity; i++) {
		cout << i << " = " << opportunity_color[i] << " ";
	}
	cout << endl;
}