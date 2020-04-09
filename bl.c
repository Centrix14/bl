/*
 * blueprint language -- this is a primitive language for creating drawings
 * v0.1
 * 09.04.2020
 * by Nifra -- ASZ
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coniox/coniox.h"
#include "proto.h"

int brush = '#';

int main(int argc, char *argv[]) {
	FILE *src = fopen("test.bl", "r");
	char form_buf[256], *form = form_buf;
	int c = 0;

	clean();

	while (!feof(src)) {
		form = form_buf;	
		c = fgetc(src);

		while (c != '/' && !feof(src)) {
			if (c != '\n') {
				*form = c;
				form++;
			}

			c = fgetc(src);
		}

		*form = c;
		form++;
		*form = '\0';

		interpret(form_buf);
	}

	fclose(src);

	setColor(BLACK, WHITE, NORMAL);
	mvCursor(0, 0);
	readKb();
	clean();

	return 0;
}

void interpret(char *form) {
	char *funcs_names[] = {"reta", "rect", "point", "slant", "brush", "sym"};
	void (*funcs[])(char*) = {reta, rect, point, slant, set_brush, sym};

	char *head = strtok(form, ":");	
	char *tail = strtok(NULL, "/");

	for (int i = 0; i < 6; i++)
		if (!strcmp(funcs_names[i], head)) (*funcs[i])(tail);
}

void reta(char *arg) {
	char *coord = strtok(arg, "|");
	char *text = strtok(NULL, "|");
	int x = atoi(strtok(coord, ";")), y = atoi(strtok(NULL, ";"));

	mvCursor(x, y);
	puts(text);
}

void rect(char *arg) {
	char *coord = strtok(arg, "|");
	char *sizes = strtok(NULL, "|");

	int x = atoi(strtok(coord, ";")), y = atoi(strtok(NULL, ";"));
	int width = atoi(strtok(sizes, ";")), lenght = atoi(strtok(NULL, ";"));

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < lenght; j++) {
			mvCursor(x+j, y+i);
			putchar(brush);
		}
	}
}

void point(char *arg) {
	int x = atoi(strtok(arg, ";")), y = atoi(strtok(arg, ";"));

	mvCursor(x, y);
	putchar(brush);
}

void slant(char *arg) {
	char *coord1 = strtok(arg, "|");	
	char *coord2 = strtok(NULL, "|");

	int x1 = atoi(strtok(coord1, ";")), y1 = atoi(strtok(NULL, ";"));	
	int x2 = atoi(strtok(coord2, ";")), y2 = atoi(strtok(NULL, ";"));

	while (x1*y1 < x2*y2) {
		mvCursor(x1, y1);
		putchar(brush);
		x1++; y1++;
	}	
}

int transform_color(char *color) {
	char *color_names[] = {"red", "green", "blue", "white", "black", "azure", "yellow", "pink", "norm", "bright"};
	int codes[] = {RED, GREEN, BLUE, WHITE, BLACK, AZURE, YELLOW, PINK, NORMAL, BRIGHT};

	for (int i = 0; i < 10; i++)
		if (!strcmp(color_names[i], color)) return codes[i];
	return BLACK;
}

void set_brush(char *arg) {
	char *c = strtok(arg, "|");	
	char *colors = strtok(NULL, "|");
	int bg, fg, bright;

	brush = *c;
	bg = transform_color(strtok(colors, ";"));
	fg = transform_color(strtok(NULL, ";"));
	bright = transform_color(strtok(NULL, ";"));

	setColor(bg, fg, bright);
}

void sym(char *arg) {
	brush = *arg;
}
