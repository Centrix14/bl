/*
 * blueprint language -- this is a primitive language for creating drawings
 * v0.4
 * 10.04.2020
 * by Nifra -- ASZ
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "coniox/coniox.h"
#include "proto.h"

int brush = '#';
int X, Y;

int main(int argc, char *argv[]) {
	FILE *src = fopen(argv[1], "r");
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
	char *funcs_names[] = {"reta", "rect", "point", "line", "brush", "sym", "~", "sleep", "circle"};
	void (*funcs[])(char*) = {reta, rect, point, line, set_brush, sym, comment, sleep, circle};

	char *head = strtok(form, ":");	
	char *tail = strtok(NULL, "/");

	int i = 0;

	for (; i < 9; i++) {
		if (!strcmp(funcs_names[i], head)){
			(*funcs[i])(tail);
			return ;
		}
	}
	if (strlen(head) > 1) puts(head);
}

void goCursor(int x, int y) {
	X = x;
	Y = y;
	if (x >= 0 && y >= 0)
		mvCursor(x, y);
}

void print(char c) {
	if (X >= 0 && Y >= 0) {
		goCursor(X, Y);
		putchar(c);
	}
	X++;
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

void line(char *arg) {
	char *coord1 = strtok(arg, "|");	
	char *coord2 = strtok(NULL, "|");

	double x1 = atof(strtok(coord1, ";")), y1 = atof(strtok(NULL, ";"));	
	double x2 = atof(strtok(coord2, ";")), y2 = atof(strtok(NULL, ";"));
	double lenght = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
	double d_x = (x2-x1)/(lenght), d_y = (y2-y1)/(lenght);

	while (x1 < x2 && y1 < y2) {
		mvCursor(x1, y1);
		putchar(brush);

		x1 += d_x; y1 += d_y;
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

void comment(char *arg) { ; }

void sleep(char *arg) {
	time_t start = time(NULL);
	char *sleep_time_str = strtok(arg, ";");
	int sleep_time = atoi(sleep_time_str);

	while ((time(NULL) - start) < sleep_time) ;
}

void circle(char *arg) {
	char *coord = strtok(arg, "|");
	char *sizes = strtok(NULL, "|");

	int x = atoi(strtok(coord, ";")), y = atoi(strtok(NULL, ";"));
	int width = atoi(sizes);
	double r = width / 2.0;

//	printf("x: %d ; y: %d ; r: %g\n", x, y, r);

	if (width == 1) {
		print(brush);
		return;
	}
	
	int point[(int)floor(r)];
	int line = 0, column = 0, is_brush = 0;
	int X, Y;
	double state;
	double S = 0;
	double xt_start, yt_start, xt_end, yt_end, k = 0.5;

	for (line = 0; line < ceil(r); line++) {
		state = ceil(r - r * sin(M_PI_4)) <= line;
		yt_start = line + 1;
		xt_start = 2*r-(sqrt(pow(r,2)-pow(yt_start-(r),2))+(r));
		for (int i = 0; i < r; i++) {
			xt_end = floor(xt_start)+1;
			yt_end = 2*r-(sqrt(pow(r,2)-pow(xt_end-(r),2))+(r));
			/*printf(" $ %g $ ", xt_end);*/
			if (ceil(yt_start) - yt_end > 1) {
				yt_end = ceil(yt_start) - 1;
				xt_end = 2*r-(sqrt(pow(r,2)-pow(yt_end-(r),2))+(r));
			}

			if (ceil(xt_end)-xt_end > 0 && ceil(yt_start)-yt_start > 0) {
				S = 1 - (xt_end-ceil(xt_end)+1)*(yt_start-ceil(yt_start)+1) / 2;
			} else if (state) {
				S = (yt_start-yt_end)*(ceil(xt_end)-xt_end+floor(xt_start)+1-xt_start) / 2;
			} else {
				S = (xt_end-xt_start)*(ceil(yt_start)-yt_start+floor(yt_end)+1-yt_end) / 2;
			}

//			printf("line: %d_%g_%g ; xt_start: %g ; yt_start: %g\t/\txt_end: %g ; yt_end: %g\n", line, state, S, xt_start, yt_start, xt_end, yt_end);

			if (S >= k || yt_start == line) {
				X = floor(xt_start);
				break;
			}

			xt_start = xt_end;
			yt_start = yt_end;
			
			if (yt_start == line) {
				X = ceil(xt_start);
				break;
			}
		}
		Y = line;
	
		goCursor(x + X, y + Y);

		for (int k = 0; k < width - 2*X; k++)
			print(brush);
		
		if (line != floor(r)+1)
			point[line] = X;
	}

	line--;
	if (width % 2 == 1) 
		line--;
	for (int i = 0; line >= 0; line--, i++) {
//		printf("line: %d ; %d ; %d ; %d ; %d\n", line, x + point[line] + 1, y + (int)ceil(r) + i + 1, width - 2*point[line], point[line]);
		goCursor(x + point[line], y + ceil(r) + i);
		for (int k = 0; k < width - 2*point[line]; k++)
			print(brush);
	}
}
