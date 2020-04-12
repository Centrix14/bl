#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "draw.h"
#include "proto.h"

void interpret(char *form, cairo_t *cr) {
	char *funcs_names[] = {"reta", "rect", "point", "line", "brush", "sym", "~", "sleep", "circle"};
	void (*funcs[])(char*, cairo_t*) = {reta, rect, point, line, set_brush, sym, comment, sleep, circle};

	char *head = strtok(form, ":");	
	char *tail = strtok(NULL, "/");

	int i = 0;

	for (; i < 9; i++) {
		if (!strcmp(funcs_names[i], head)){
			(*funcs[i])(tail, cr);
			return ;
		}
	}
	if (strlen(head) > 1) puts(head);
}

void reta(char *arg, cairo_t *cr) {
	char *coord = strtok(arg, "|");
	char *text = strtok(NULL, "|");
	int x = atoi(strtok(coord, ";")), y = atoi(strtok(NULL, ";"));

	draw_text(cr, text, mm_to_pix(x), mm_to_pix(y), 20);
}

void rect(char *arg, cairo_t *cr) {
	char *coord = strtok(arg, "|");
	char *sizes = strtok(NULL, "|");

	int x = atoi(strtok(coord, ";")), y = atoi(strtok(NULL, ";"));
	int width = atoi(strtok(sizes, ";")), lenght = atoi(strtok(NULL, ";"));

	draw_rect(cr, mm_to_pix(x), mm_to_pix(y), mm_to_pix(lenght), mm_to_pix(width));
}

void point(char *arg, cairo_t *cr) {
	int x = atoi(strtok(arg, ";")), y = atoi(strtok(arg, ";"));

	draw_point(cr, mm_to_pix(x), mm_to_pix(y));
}

void line(char *arg, cairo_t *cr) {
	char *coord1 = strtok(arg, "|");
	char *coord2 = strtok(NULL, "|");

	double x1 = atof(strtok(coord1, ";")), y1 = atof(strtok(NULL, ";"));
	double x2 = atof(strtok(coord2, ";")), y2 = atof(strtok(NULL, ";"));

	draw_line(cr, mm_to_pix(x1), mm_to_pix(y1), mm_to_pix(x2), mm_to_pix(y2));
}

void circle(char *arg, cairo_t *cr) {
	char *coord = strtok(arg, "|");
	char *diameter = strtok(NULL, "|");

	double x = atof(strtok(coord, ";")), y = atof(strtok(NULL, ";"));
	double d = atof(diameter);

	draw_circle(cr, mm_to_pix(x), mm_to_pix(y), mm_to_pix(d/2));
}

void set_brush(char *arg, cairo_t *cr) { ; }

void sym(char *arg, cairo_t *cr) { ; }

void comment(char *arg, cairo_t *cr) { ; }

void sleep(char *arg, cairo_t *cr) {
	time_t start = time(NULL);
	char *sleep_time_str = strtok(arg, ";");
	int sleep_time = atoi(sleep_time_str);

	while ((time(NULL) - start) < sleep_time) ;
}
