#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "proto.h"

#define PI 3.14159265359

double grades_to_rad(double grad) {
	return grad * (PI / 180);
}

void add_point(GtkWidget *bttn, char *src) {
	char str[256] = "", *x = NULL, *y = NULL;
	FILE *dst = fopen(src, "a");

	strcpy(str, get_coord());
	if (is_empty(str))
		return ;	

	x = strtok(str, " ");
	y = strtok(NULL, " ");

	if (dst)
		fprintf(dst, "point:%s;%s/\n", x, y);	
	fclose(dst);
}

void add_line(GtkWidget *bttn, char *src) {
	char str[256] = "", x1[64] = "", y1[64] = "", x2[64] = "", y2[64] = "";
	FILE *dst = fopen(src, "a");

	strcpy(str, get_coord());
	if (is_empty(str))
		return ;	

	strcpy(x1, strtok(str, " "));
	strcpy(y1, strtok(NULL, " "));

	strcpy(str, get_first());
	if (!is_empty(str)) {
		strcpy(x2, strtok(str, " "));
		strcpy(y2, strtok(NULL, " "));
	}
	else {
		char radii_str[64] = "", angle_str[64] = "";
		double radii = 0, angle = 0, abscissa = 0, ordinate = 0;

		strcpy(str, get_second());

		if (is_empty(str))
			return ;	

		strcpy(radii_str, strtok(str, " "));
		strcpy(angle_str, strtok(NULL, " "));

		radii = atof(radii_str);
		angle = atof(angle_str);

		abscissa = sin(grades_to_rad(angle)) * radii;
		ordinate = sqrt(pow(radii, 2) - pow(abscissa, 2));

		sprintf(x2, "%f", ordinate + atof(y1));
		sprintf(y2, "%f", abscissa + atof(x1));
	}

	if (is_empty(x1) || is_empty(y1) || is_empty(x2) || is_empty(y2))
		return ;	

	if (dst)
		fprintf(dst, "line:%s;%s|%s;%s/\n", x1, y1, x2, y2);	
	fclose(dst);
}

void add_circle(GtkWidget *bttn, char *src) {
	char str[256] = "", *x = NULL, *y = NULL, d[64] = "";
	FILE *dst = fopen(src, "a");
	
	strcpy(str, get_coord());
	if (is_empty(str))
		return ;	

	x = strtok(str, " ");
	y = strtok(NULL, " ");
	
	strcpy(d, get_first());

	if (!x || !y || is_empty(d))
		return ;	
	fprintf(dst, "circle:%s;%s|%s/\n", x, y, d);
	fclose(dst);
}

void add_rect(GtkWidget *bttn, char *src) {
	char str[256] = "", x[64] = "", y[64] = "", width[64] = "", height[64] = "";
	FILE *dst = fopen(src, "a");

	strcpy(str, get_coord());
	if (is_empty(str))
		return ;

	strcpy(x, strtok(str, " "));
	strcpy(y, strtok(NULL, " "));

	strcpy(str, get_first());
	if (!is_empty(str)) {
		char *x2_str = NULL, *y2_str = NULL;

		x2_str = strtok(str, " ");
		y2_str = strtok(NULL, " ");

		sprintf(width, "%d", atoi(x2_str) - atoi(x));
		sprintf(height, "%d", atoi(y2_str) - atoi(y));
	}
	else {
		strcpy(str, get_second());	
		if (is_empty(str))
			return ;	

		strcpy(width, strtok(str, " "));
		strcpy(height, strtok(NULL, " "));
	}

	if (is_empty(x) || is_empty(y) || is_empty(width) || is_empty(height))
		return ;	

	fprintf(dst, "rect:%s;%s|%s;%s/\n", x, y, width, height);
	fclose(dst);
}

void add_arc(GtkWidget *bttn, char *src) {
	char str[256] = "", x[64] = "", y[64] = "", a1[54] = "", a2[64] = "", r[64] = "";
	FILE *dst = fopen(src, "a");

	strcpy(str, get_coord());
	if (is_empty(str))
		return ;

	strcpy(x, strtok(str, " "));
	strcpy(y, strtok(NULL, " "));

	strcpy(r, get_first());
	if (is_empty(r))
		return ;

	strcpy(str, get_second());
	if (is_empty(str))
		return ;

	strcpy(a1, strtok(str, " "));
	strcpy(a2, strtok(NULL, " "));

	if (is_empty(x) || is_empty(y) || is_empty(a1) || is_empty(a2))
		return ;

	fprintf(dst, "arc:%s;%s|%s|%s;%s/\n", x, y, r, a1, a2);
	fclose(dst);
}
