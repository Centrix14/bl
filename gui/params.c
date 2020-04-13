#include <string.h>

double PIX_PER_MM = 5;
double grid_fg_red = 0.2, grid_fg_green = 0.2, grid_fg_blue = 0.2;
double grid_thick = 1;
double point_r = 4;

double bg_red = 0, bg_green = 0, bg_blue = 0;
double fg_red = 0, fg_green = 0.5, fg_blue = 1;

double thick = 2;

double uni_get(char *param) {
	char *params[] = {"ppm", "gfr", "gfg", "gfb", "gt", "pr", "br", "bg", "bb", "fr", "fg", "fb", "th"};
	double *values[] = {&PIX_PER_MM, &grid_fg_red, &grid_fg_green, &grid_fg_blue, &grid_thick, &point_r, &bg_red, &bg_green, &bg_blue, &fg_red, &fg_green, &fg_blue, &thick};

	for (int i = 0; i < 13; i++)
		if (!strcmp(params[i], param)) return *(values[i]);
	return 0;
}

void uni_set(char *param, double new_value) {
	char *params[] = {"ppm", "gfr", "gfg", "gfb", "gt", "pr", "br", "bg", "bb", "fr", "fg", "fb", "th"};
	double *values[] = {&PIX_PER_MM, &grid_fg_red, &grid_fg_green, &grid_fg_blue, &grid_thick, &point_r, &bg_red, &bg_green, &bg_blue, &fg_red, &fg_green, &fg_blue, &thick};

	for (int i = 0; i < 13; i++) {
		if (!strcmp(params[i], param)) {
			*(values[i]) = new_value;
			break;
		}
	}
}
