#include <stdio.h>
#include "proto.h"

void add_to_file_bttn_click(GtkWidget *bttn, GtkWidget *entry) {
	FILE *dst = fopen(get_fname(), "a");
	char *str = (char*)(gtk_entry_get_text(GTK_ENTRY(entry)));

	fputs(str, dst);
	fclose(dst);
}
