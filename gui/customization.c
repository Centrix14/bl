#include <gtk/gtk.h>
#include <stdlib.h>
#include "proto.h"

void ppm_apply_click(GtkWidget *bttn, GtkWidget *entry) {
	double new_ppm = atof(gtk_entry_get_text(GTK_ENTRY(entry)));	

	if (new_ppm > 0)
		uni_set("ppm", new_ppm);
}
