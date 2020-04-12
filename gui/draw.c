#include <gtk/gtk.h>

double PIX_PER_MM = 5;
double grid_fg_red = 0.2, grid_fg_green = 0.2, grid_fg_blue = 0.2;
double grid_thick = 1;
double point_r = 4;

double mm_to_pix(double mm) {
	return mm * PIX_PER_MM;
}

void draw_line(cairo_t *cr, double x1, double y1, double x2, double y2) {
	cairo_move_to(cr, x1, y1);
	cairo_line_to(cr, x2, y2);

	cairo_stroke(cr);
}

void draw_grid(cairo_t *cr, guint width, guint height, guint step) {
	cairo_set_source_rgb(cr, grid_fg_red, grid_fg_green, grid_fg_blue);	
	cairo_set_line_width(cr, grid_thick);

	for (int i = 0; i < (height/step); i++) {
		draw_line(cr, 0, step * i, width, step * i);	
	}
	for (int i = 0; i < (width/step); i++) {
		draw_line(cr, step * i, 0, step * i, height);	
	}

	cairo_stroke(cr);
}

void draw_point(cairo_t *cr, double x, double y) {
	cairo_arc (cr, x, y, point_r, 0, 2 * G_PI);

	cairo_fill(cr);
}

void draw_circle(cairo_t *cr, double x, double y, double radii) {
	cairo_arc(cr, x, y, radii, 0, 2 * G_PI);
	cairo_stroke(cr);

	draw_point(cr, x, y);
}

void draw_rect(cairo_t *cr, double x, double y, double width, double height) {
	cairo_rectangle(cr, x, y, width, height);

	cairo_stroke(cr);
}

void draw_text(cairo_t *cr, const char *text, double x, double y, int size) {
	cairo_text_extents_t te;

	cairo_select_font_face(cr, "Corbel",
	    CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, size);

	cairo_text_extents(cr, text, &te);
	cairo_move_to(cr, x, y);

	cairo_show_text(cr, text);
	cairo_fill(cr);
}
