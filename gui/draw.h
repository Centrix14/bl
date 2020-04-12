#ifndef __GUI_INTERPRETER_FOR_BLUE_PRINT_LANGUAGE_H_INCLUDED__
#define __GUI_INTERPRETER_FOR_BLUE_PRINT_LANGUAGE_H_INCLUDED__

void draw_line(cairo_t *cr, double x1, double y1, double x2, double y2);
void draw_grid(cairo_t *cr, guint width, guint height, guint step);
void draw_point(cairo_t *cr, double x, double y);
void draw_rect(cairo_t *cr, double x, double y, double width, double height);
void draw_circle(cairo_t *cr, double x, double y, double radii);
void draw_text(cairo_t *cr, const char *text, double x, double y, int size);

double mm_to_pix(double mm);

#endif
