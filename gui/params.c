#include <string.h>
#include <stdlib.h>
#include "proto.h"

#define LEN 14

double PIX_PER_MM = 5.0;
double grid_fg_red = 0.2, grid_fg_green = 0.2, grid_fg_blue = 0.2;
double grid_thick = 1;
double point_r = 4;

double bg_red = 0, bg_green = 0, bg_blue = 0;
double fg_red = 0, fg_green = 0.5, fg_blue = 1;

double thick = 2;

double show_grid = 1.0f;

char *params[] = {"ppm", "gfr", "gfg", "gfb", "gt", "pr", "br", "bg", "bb", "fr", "fg", "fb", "th", "sg"};
double *values[] = {&PIX_PER_MM, &grid_fg_red, &grid_fg_green, &grid_fg_blue, &grid_thick, &point_r, &bg_red, &bg_green, &bg_blue, &fg_red, &fg_green, &fg_blue, &thick, &show_grid};

double uni_get(char *param) {
	for (int i = 0; i < LEN; i++)
		if (!strcmp(params[i], param)) return *(values[i]);
	return 0;
}

void uni_set(char *param, double new_value) {
	for (int i = 0; i < LEN; i++) {
		if (!strcmp(params[i], param)) {
			*(values[i]) = new_value;
			break;
		}
	}
}
