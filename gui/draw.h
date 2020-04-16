#ifndef __GUI_INTERPRETER_FOR_BLUE_PRINT_LANGUAGE_H_INCLUDED__
#define __GUI_INTERPRETER_FOR_BLUE_PRINT_LANGUAGE_H_INCLUDED__

void draw_line(cairo_t*, double, double, double, double);
void draw_grid(cairo_t*, guint, guint, guint);
void draw_point(cairo_t*, double, double);
void draw_rect(cairo_t*, double, double, double, double);
void draw_circle(cairo_t*, double, double, double);
void draw_text(cairo_t*, const char*, double, double, int);
void draw_arc(cairo_t*, double, double, double, double, double);

double mm_to_pix(double);

#endif
