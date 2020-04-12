/*
 * gbl -- graphical bl interpreter
 * v0.1
 * 12.04.2020
 * Nifra -- ASZ
 */

#include <gtk/gtk.h>
#include "proto.h"
#include "draw.h"

gboolean draw_callback(GtkWidget*, cairo_t*, char*);

double bg_red = 0, bg_green = 0, bg_blue = 0;
double fg_red = 0, fg_green = 0.5, fg_blue = 1;

double thick = 2;

int main(int argc, char *argv[]) {
	GtkWidget *window;	
	GtkWidget *main_box;
	GtkWidget *draw_area, *test_label;

	cairo_t *cr;

	gtk_init(&argc, &argv);

	// init window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "gbl");
	gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);
	gtk_window_set_default_icon_from_file("gbl.ico", NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// init main_box
	main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

	// init drawing area
	draw_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(draw_area, 800, 800);
	g_signal_connect (G_OBJECT(draw_area), "draw",
                    G_CALLBACK(draw_callback), argv[1]);

	// init test label
	test_label = gtk_label_new("test_label");

	// pack main_box
	gtk_box_pack_start(GTK_BOX(main_box), test_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(main_box), draw_area, TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(window), main_box);
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, char *file_name) {
	FILE *src = fopen(file_name, "r");
	char form_buf[256], *form = form_buf;
	guint width, height;
	int c = 0;

	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	cairo_set_source_rgb(cr, bg_red, bg_green, bg_blue);
	cairo_paint(cr);

	// drawing grid
	draw_grid(cr, width, height, mm_to_pix(5));
	
	cairo_set_source_rgb(cr, fg_red, fg_green, fg_blue);
	cairo_set_line_width(cr, thick);

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

		interpret(form_buf, cr);
	}

	fclose(src);
	return FALSE;
}
