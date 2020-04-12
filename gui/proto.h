#ifndef __BLUE_PRINT_LANGUAGE_PROTO_H_INCLUDED__
#define __BLUE_PRINT_LANGUAGE_PROTO_H_INCLUDED__

#include <gtk/gtk.h>

#define SIZE 32

void interpret(char*, cairo_t*);

void reta(char*, cairo_t*),
	 rect(char*, cairo_t*),
	 point(char*, cairo_t*),
	 line(char*, cairo_t*),
	 set_brush(char*, cairo_t*),
	 sym(char*, cairo_t*),
	 comment(char*, cairo_t*),
	 sleep(char*, cairo_t*),
	 circle(char*, cairo_t*);

#endif
