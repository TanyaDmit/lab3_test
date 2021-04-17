#include "class_for_color.h"

using namespace std;

enum type_of_color_t {
	light_green = 13434624, pink = 16711833, lilac = 10027212, dark_blue = 3342591,
	turquoise = 65535, dark_green = 65280, light_blue = 39423,
	purple = 6684876, yellow = 16776960, swampy = 102
};

static int how_many = 0;

static int opportunity_color[10] = { light_green, pink, lilac, dark_blue,
						  turquoise, dark_green,  light_blue,
						  purple, yellow, swampy };

int class_for_color::get_color(int index) {
	return (int)opportunity_color[index % 10];
}

void class_for_color::out_all(void)
{
	for (int i = 0; i < sizeof(opportunity_color) / sizeof(type_of_color_t); i++) {
		cout << i << " = " << opportunity_color[i] << " ";
	}
	cout << endl;
}