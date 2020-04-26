/*
 * gbl -- graphical bl interpreter
 * v0.8
 * 26.04.2020
 * Nifra -- ASZ
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include "proto.h"
#include "draw.h"

gboolean draw_callback(GtkWidget*, cairo_t*, char*);
void cust_bttn_click(GtkWidget*, GtkWidget*);
void dd_bttn_click(GtkWidget*, GtkWidget*);

int main(int argc, char *argv[]) {
	GtkWidget *window;	
	GtkWidget *main_box, *menu_box;
	GtkWidget *draw_area, *cust_bttn, *dd_bttn;
	FILE *src = NULL;

	if (argc != 2) {
		fprintf(stderr, "%s: %s <script-name>\n", argv[0], argv[0]);
		return 0;
	}

	src = fopen(argv[1], "r");
	if (!src) {
		fclose(src);
		fclose(fopen(argv[1], "w"));
	}
	set_fname(argv[1]);

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
	g_signal_connect(G_OBJECT(cust_bttn), "clicked", G_CALLBACK(cust_bttn_click), window);

	// init dynamic_draw bttn
	dd_bttn = gtk_button_new_with_label("dd");
	g_signal_connect(G_OBJECT(dd_bttn), "clicked", G_CALLBACK(dd_bttn_click), window);
	
	// init and pack menu_box
	menu_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(menu_box), cust_bttn, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(menu_box), dd_bttn, TRUE, TRUE, 5);

	// pack main_box
	gtk_box_pack_start(GTK_BOX(main_box), menu_box, FALSE, FALSE, 5);
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
		perror("gbl");	
		exit(0);
	}

	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	cairo_translate(cr, 0, height);
	cairo_rotate(cr, grades_to_rad(-90));
	cairo_set_source_rgb(cr, uni_get("br"), uni_get("bg"), uni_get("bb"));
	cairo_paint(cr);

	// drawing grid
	if (uni_get("sg"))
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

void cust_bttn_click(GtkWidget *bttn, GtkWidget *parent_window) {
	GtkWidget *cust_dialog, *dialog_content;

	GtkWidget *ppm_label, *ppm_entry, *ppm_apply_bttn, *ppm_box;
	GtkWidget *sg_label, *sg_entry, *sg_apply_bttn, *sg_box;
	GtkWidget *fc_label, *fc_entry, *fc_apply_bttn, *fc_box;
	GtkWidget *bc_label, *bc_entry, *bc_apply_bttn, *bc_box;
	GtkWidget *gc_label, *gc_entry, *gc_apply_bttn, *gc_box;
	GtkWidget *lw_label, *lw_entry, *lw_apply_bttn, *lw_box;
	GtkWidget *gw_label, *gw_entry, *gw_apply_bttn, *gw_box;
	GtkWidget *pr_label, *pr_entry, *pr_apply_bttn, *pr_box;
	GtkWidget *hor_sep1, *hor_sep2;

	GtkWidget *dialog_box;

	cust_dialog = gtk_dialog_new_with_buttons("customization", GTK_WINDOW(parent_window), (GtkDialogFlags)NULL, NULL, GTK_RESPONSE_NONE, NULL);
	dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(cust_dialog));
	g_signal_connect_swapped(cust_dialog, "response", G_CALLBACK(gtk_widget_destroy), cust_dialog);

	// init ppm row
	ppm_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	ppm_entry = gtk_entry_new();
	ppm_apply_bttn = gtk_button_new_with_label("apply");
	ppm_label = gtk_label_new("ppm");
	g_signal_connect(G_OBJECT(ppm_apply_bttn), "clicked", G_CALLBACK(ppm_apply_click), ppm_entry);

	// init sg row
	sg_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	sg_label = gtk_label_new("show grid");
	sg_entry = gtk_entry_new();
	sg_apply_bttn = gtk_button_new_with_label("apply");
	g_signal_connect(G_OBJECT(sg_apply_bttn), "clicked", G_CALLBACK(sg_apply_click), sg_entry);

	// init fc row
	fc_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	fc_label = gtk_label_new("foreground color");
	fc_entry = gtk_entry_new();
	fc_apply_bttn = gtk_button_new_with_label("apply");
	g_signal_connect(G_OBJECT(fc_apply_bttn), "clicked", G_CALLBACK(fc_apply_click), fc_entry);

	// init bc row
	bc_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	bc_label = gtk_label_new("background color");
	bc_entry = gtk_entry_new();
	bc_apply_bttn = gtk_button_new_with_label("apply");
	g_signal_connect(G_OBJECT(bc_apply_bttn), "clicked", G_CALLBACK(bc_apply_click), bc_entry);

	// init gc row
	gc_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gc_label = gtk_label_new("grid color");
	gc_entry = gtk_entry_new();
	gc_apply_bttn = gtk_button_new_with_label("apply");
	g_signal_connect(G_OBJECT(gc_apply_bttn), "clicked", G_CALLBACK(gc_apply_click), gc_entry);

	// init lw row
	lw_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	lw_label = gtk_label_new("line width");
	lw_entry = gtk_entry_new();
	lw_apply_bttn = gtk_button_new_with_label("apply");
	g_signal_connect(G_OBJECT(lw_apply_bttn), "clicked", G_CALLBACK(lw_apply_click), lw_entry);

	// init gw row
	gw_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gw_label = gtk_label_new("grid line width");
	gw_entry = gtk_entry_new();
	gw_apply_bttn = gtk_button_new_with_label("apply");
	g_signal_connect(G_OBJECT(gw_apply_bttn), "clicked", G_CALLBACK(gw_apply_click), gw_entry);

	// init pr row
	pr_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	pr_label = gtk_label_new("point radius");
	pr_entry = gtk_entry_new();
	pr_apply_bttn = gtk_button_new_with_label("apply");
	g_signal_connect(G_OBJECT(pr_apply_bttn), "clicked", G_CALLBACK(pr_apply_click), pr_entry);

	// pack ppm row
	gtk_box_pack_start(GTK_BOX(ppm_box), ppm_label, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(ppm_box), ppm_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(ppm_box), ppm_apply_bttn, FALSE, FALSE, 5);

	// pack sg row
	gtk_box_pack_start(GTK_BOX(sg_box), sg_label, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(sg_box), sg_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(sg_box), sg_apply_bttn, FALSE, FALSE, 5);

	// pack fc row
	gtk_box_pack_start(GTK_BOX(fc_box), fc_label, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(fc_box), fc_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(fc_box), fc_apply_bttn, FALSE, FALSE, 5);

	// pack bc row
	gtk_box_pack_start(GTK_BOX(bc_box), bc_label, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(bc_box), bc_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(bc_box), bc_apply_bttn, FALSE, FALSE, 5);

	// pack gc row
	gtk_box_pack_start(GTK_BOX(gc_box), gc_label, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(gc_box), gc_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(gc_box), gc_apply_bttn, FALSE, FALSE, 5);

	// pack lw row
	gtk_box_pack_start(GTK_BOX(lw_box), lw_label, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(lw_box), lw_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(lw_box), lw_apply_bttn, FALSE, FALSE, 5);

	// pack gw row
	gtk_box_pack_start(GTK_BOX(gw_box), gw_label, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(gw_box), gw_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(gw_box), gw_apply_bttn, FALSE, FALSE, 5);

	// pack pr row
	gtk_box_pack_start(GTK_BOX(pr_box), pr_label, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pr_box), pr_entry, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pr_box), pr_apply_bttn, FALSE, FALSE, 5);

	// pack dialog box
	dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	hor_sep1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	hor_sep2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

	gtk_box_pack_start(GTK_BOX(dialog_box), fc_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), bc_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), gc_box, TRUE, FALSE, 5);

	gtk_box_pack_start(GTK_BOX(dialog_box), hor_sep1, TRUE, TRUE, 5);

	gtk_box_pack_start(GTK_BOX(dialog_box), lw_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), gw_box, TRUE, FALSE, 5);

	gtk_box_pack_start(GTK_BOX(dialog_box), hor_sep2, TRUE, TRUE, 5);

	gtk_box_pack_start(GTK_BOX(dialog_box), pr_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), ppm_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), sg_box, TRUE, FALSE, 5);

	gtk_container_add(GTK_CONTAINER(dialog_content), dialog_box);
	gtk_widget_show_all(cust_dialog);
}

void dd_bttn_click(GtkWidget *bttn, GtkWidget *parent_window) {
	GtkWidget *dd_dialog, *dialog_content;

	GtkWidget *dialog_box;
	GtkWidget *change_row;

	GtkWidget *change_label, *change_rect_bttn, *change_line_bttn, *change_point_bttn, *change_circle_bttn, *change_arc_bttn;

	dd_dialog = gtk_dialog_new_with_buttons("dynamic draw", GTK_WINDOW(parent_window), (GtkDialogFlags)NULL, NULL, GTK_RESPONSE_NONE, NULL);
	dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(dd_dialog));
	g_signal_connect_swapped(dd_dialog, "response", G_CALLBACK(gtk_widget_destroy), dd_dialog);

	// init change_row elements
	change_label = gtk_label_new("Select a primitive");
	change_point_bttn = gtk_button_new_with_label("point");
	change_line_bttn = gtk_button_new_with_label("line");
	change_circle_bttn = gtk_button_new_with_label("circle");
	change_rect_bttn = gtk_button_new_with_label("rectangle");
	change_arc_bttn = gtk_button_new_with_label("arc");

	// pack change_row
	change_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_pack_start(GTK_BOX(change_row), change_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(change_row), change_point_bttn, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(change_row), change_line_bttn, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(change_row), change_circle_bttn, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(change_row), change_rect_bttn, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(change_row), change_arc_bttn, TRUE, TRUE, 5);

	// pack dialog box
	dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), change_row, TRUE, FALSE, 5);

	g_signal_connect(G_OBJECT(change_point_bttn), "clicked", G_CALLBACK(choose_bttns_click), dd_dialog);
	g_signal_connect(G_OBJECT(change_line_bttn), "clicked", G_CALLBACK(choose_bttns_click), dd_dialog);
	g_signal_connect(G_OBJECT(change_circle_bttn), "clicked", G_CALLBACK(choose_bttns_click), dd_dialog);
	g_signal_connect(G_OBJECT(change_rect_bttn), "clicked", G_CALLBACK(choose_bttns_click), dd_dialog);
	g_signal_connect(G_OBJECT(change_arc_bttn), "clicked", G_CALLBACK(choose_bttns_click), dd_dialog);

	gtk_container_add(GTK_CONTAINER(dialog_content), dialog_box);
	gtk_widget_show_all(dd_dialog);
}
