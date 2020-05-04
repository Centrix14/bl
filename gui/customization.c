#include <gtk/gtk.h>
#include <stdlib.h>
#include "proto.h"

void ppm_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	double new_ppm = atof(gtk_entry_get_text(GTK_ENTRY(entry)));	

	if (new_ppm > 0)
		uni_set("ppm", new_ppm);
}

void sg_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	int is_show_grid = atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
	uni_set("sg", is_show_grid);
}

void fc_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	char theme[256] = "";
	char *red = NULL, *green = NULL, *blue = NULL;

	strcpy(theme, (char*)gtk_entry_get_text(GTK_ENTRY(entry)));

	red = strtok(theme, " ");
	green = strtok(NULL, " ");
	blue = strtok(NULL, " ");

	uni_set("fr", atof(red));
	uni_set("fg", atof(green));
	uni_set("fb", atof(blue));
}

void bc_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	char theme[256] = "";
	char *red = NULL, *green = NULL, *blue = NULL;

	strcpy(theme, (char*)gtk_entry_get_text(GTK_ENTRY(entry)));

	red = strtok(theme, " ");
	green = strtok(NULL, " ");
	blue = strtok(NULL, " ");

	uni_set("br", atof(red));
	uni_set("bg", atof(green));
	uni_set("bb", atof(blue));
}

void gc_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	char theme[256] = "";
	char *red = NULL, *green = NULL, *blue = NULL;

	strcpy(theme, (char*)gtk_entry_get_text(GTK_ENTRY(entry)));

	red = strtok(theme, " ");
	green = strtok(NULL, " ");
	blue = strtok(NULL, " ");

	uni_set("gfr", atof(red));
	uni_set("gfg", atof(green));
	uni_set("gfb", atof(blue));
}

void lw_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	double new_width = atof(gtk_entry_get_text(GTK_ENTRY(entry)));

	if (new_width > 0)
		uni_set("th", new_width);	
}

void gw_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	double new_width = atof(gtk_entry_get_text(GTK_ENTRY(entry)));

	if (new_width > 0)
		uni_set("gt", new_width);	
}

void pr_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	double new_radius = atof(gtk_entry_get_text(GTK_ENTRY(entry)));

	if (new_radius > 0)
		uni_set("pr", new_radius);	
}

void gs_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	double new_grid_step = atof(gtk_entry_get_text(GTK_ENTRY(entry)));

	if (new_grid_step > 0)
		uni_set("gs", new_grid_step);	
}
