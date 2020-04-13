/*
 * gbl -- graphical bl interpreter
 * v0.1
 * 12.04.2020
 * Nifra -- ASZ
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include "proto.h"
#include "draw.h"

gboolean draw_callback(GtkWidget*, cairo_t*, char*);
void cust_bttn_click(GtkWidget*, gpointer);

int main(int argc, char *argv[]) {
	GtkWidget *window;	
	GtkWidget *main_box;
	GtkWidget *draw_area, *cust_bttn;

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

	// init customization bttn
	cust_bttn = gtk_button_new_with_label("cust");
	g_signal_connect(G_OBJECT(cust_bttn), "clicked", G_CALLBACK(cust_bttn_click), NULL);

	// pack main_box
	gtk_box_pack_start(GTK_BOX(main_box), cust_bttn, FALSE, FALSE, 5);
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

	if (!src) {
		fprintf(stderr, "gbl: gbl <script-name\n>");
		exit(0);
	}

	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	cairo_set_source_rgb(cr, uni_get("br"), uni_get("bg"), uni_get("bb"));
	cairo_paint(cr);

	// drawing grid
	draw_grid(cr, width, height, mm_to_pix(5));
	
	cairo_set_source_rgb(cr, uni_get("fr"), uni_get("fg"), uni_get("fb"));
	cairo_set_line_width(cr, uni_get("th"));

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

void cust_bttn_click(GtkWidget *bttn, gpointer data) {
	GtkWidget *cust_dialog, *dialog_content;
	GtkWidget *ppm_entry, *ppm_apply_bttn;
	GtkWidget *dialog_box, *ppm_box;

	cust_dialog = gtk_dialog_new_with_buttons("Customization", NULL, (GtkDialogFlags)NULL, NULL);
	dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(cust_dialog));

	// init ppm row
	ppm_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	ppm_entry = gtk_entry_new();
	ppm_apply_bttn = gtk_button_new_with_label("apply");
	g_signal_connect(G_OBJECT(ppm_apply_bttn), "clicked", G_CALLBACK(ppm_apply_click), ppm_entry);

	// pack ppm row
	gtk_box_pack_start(GTK_BOX(ppm_box), ppm_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(ppm_box), ppm_apply_bttn, FALSE, FALSE, 5);

	// pack dialog box
	dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), ppm_box, TRUE, FALSE, 5);

	gtk_container_add(GTK_CONTAINER(dialog_content), dialog_box);
	gtk_widget_show_all(cust_dialog);
}
