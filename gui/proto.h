#ifndef __BLUE_PRINT_LANGUAGE_PROTO_H_INCLUDED__
#define __BLUE_PRINT_LANGUAGE_PROTO_H_INCLUDED__

#include <gtk/gtk.h>

#define SIZE 32

#define DEFAULT_PPM "5"
#define DEFAULT_SG "1"

void interpret(char*, cairo_t*);

void reta(char*, cairo_t*),
	 rect(char*, cairo_t*),
	 point(char*, cairo_t*),
	 line(char*, cairo_t*),
	 set_brush(char*, cairo_t*),
	 sym(char*, cairo_t*),
	 comment(char*, cairo_t*),
	 sleep(char*, cairo_t*),
	 circle(char*, cairo_t*),
	 arc(char*, cairo_t*);

double uni_get(char*);
void uni_set(char*, double);

void ppm_apply_click(GtkWidget*, GtkWidget*),
	 sg_apply_click(GtkWidget*, GtkWidget*),
	 fc_apply_click(GtkWidget*, GtkWidget*),
	 bc_apply_click(GtkWidget*, GtkWidget*),
	 gc_apply_click(GtkWidget*, GtkWidget*),
	 lw_apply_click(GtkWidget*, GtkWidget*),
	 gw_apply_click(GtkWidget*, GtkWidget*),
	 pr_apply_click(GtkWidget*, GtkWidget*);

#endif
