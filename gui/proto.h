#ifndef __BLUE_PRINT_LANGUAGE_PROTO_H_INCLUDED__
#define __BLUE_PRINT_LANGUAGE_PROTO_H_INCLUDED__

#include <gtk/gtk.h>

#define SIZE 32
#define HELP_FILE "help.txt"

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
	 pr_apply_click(GtkWidget*, GtkWidget*),
	 gs_apply_click(GtkWidget*, GtkWidget*);

void pb_click(GtkWidget*),
	 lb_click(GtkWidget*),
	 cb_click(GtkWidget*),
	 rb_click(GtkWidget*),
	 ab_click(GtkWidget*);

void choose_bttns_click(GtkWidget*, GtkWidget*);
char *get_coord(),
	 *get_first(),
	 *get_second();

void set_fname(char*);
char *get_fname();

void add_point(GtkWidget*, char*),
	 add_line(GtkWidget*, char*),
	 add_circle(GtkWidget*, char*),
	 add_rect(GtkWidget*, char*),
	 add_arc(GtkWidget*, char*);

int is_empty(char *str);

double grades_to_rad(double grad);

void create(char*);
void destroy();
char *read_and_fill(char*);

void add_to_file_bttn_click(GtkWidget *bttn, GtkWidget *entry);

#endif
