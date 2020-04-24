#include <gtk/gtk.h>
#include "proto.h"

void choose_bttns_click(GtkWidget *bttn, GtkWidget *dialog) {
	char *types[] = {"point", "line", "circle", "rectangle"};
	void (*handler[])(GtkWidget*) = {pb_click, lb_click, cb_click, rb_click};

	for (int i = 0; i < 4; i++)
		if (!strcmp(gtk_button_get_label(GTK_BUTTON(bttn)), types[i])) (*handler[i])(dialog);
}

void pb_click(GtkWidget *dialog) {
	GtkWidget *pb_dialog, *dialog_content;
	GtkWidget *dialog_box;

	GtkWidget *coord_box;

	GtkWidget *description_label, *add_bttn;
	GtkWidget *coord_label;
	GtkWidget *coord_entry;

	pb_dialog = gtk_dialog_new_with_buttons("point", (GtkWindow*)NULL, (GtkDialogFlags)NULL, NULL, GTK_RESPONSE_NONE, NULL);
	dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(pb_dialog));
	g_signal_connect_swapped(pb_dialog, "response", G_CALLBACK(gtk_widget_destroy), pb_dialog);

	// init elements
	description_label = gtk_label_new("separate all data with a space, for example: 20 50");
	add_bttn = gtk_button_new_with_label("add");

	coord_label = gtk_label_new("coordinates");
	coord_entry = gtk_entry_new();

	// init boxes
	coord_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	// pack boxes
	gtk_box_pack_start(GTK_BOX(coord_box), coord_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(coord_box), coord_entry, TRUE, TRUE, 5);	

	// pack dialog_box
	dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), description_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), coord_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), add_bttn, TRUE, TRUE, 5);

	gtk_container_add(GTK_CONTAINER(dialog_content), dialog_box);
	gtk_widget_show_all(pb_dialog);
}

void lb_click(GtkWidget *dialog) {
	GtkWidget *lb_dialog, *dialog_content;
	GtkWidget *dialog_box;

	GtkWidget *coord_box, *first_box, *second_box;

	GtkWidget *description_label, *add_bttn;
	GtkWidget *first_label, *second_label, *coord_label;
	GtkWidget *first_entry, *second_entry, *coord_entry;
	GtkWidget *vertical_sep;

	lb_dialog = gtk_dialog_new_with_buttons("line", (GtkWindow*)NULL, (GtkDialogFlags)NULL, NULL, GTK_RESPONSE_NONE, NULL);
	dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(lb_dialog));
	g_signal_connect_swapped(lb_dialog, "response", G_CALLBACK(gtk_widget_destroy), lb_dialog);

	// init elements
	description_label = gtk_label_new("separate all data with a space, for example: 20 50");
	add_bttn = gtk_button_new_with_label("add");

	coord_label = gtk_label_new("coordinates");
	coord_entry = gtk_entry_new();

	first_label = gtk_label_new("by 2 points");
	second_label = gtk_label_new("by lenght & angle");
	first_entry = gtk_entry_new();
	second_entry = gtk_entry_new();

	vertical_sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

	// init boxes
	coord_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	first_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	second_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	// pack boxes
	gtk_box_pack_start(GTK_BOX(coord_box), coord_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(coord_box), coord_entry, TRUE, TRUE, 5);	

	gtk_box_pack_start(GTK_BOX(first_box), first_label, FALSE, FALSE, 5);	
	gtk_box_pack_start(GTK_BOX(first_box), first_entry, TRUE, TRUE, 5);

	gtk_box_pack_start(GTK_BOX(second_box), second_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(second_box), second_entry, TRUE, TRUE, 5);

	// pack dialog_box
	dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), description_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), coord_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), vertical_sep, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), first_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), second_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), add_bttn, TRUE, TRUE, 5);

	gtk_container_add(GTK_CONTAINER(dialog_content), dialog_box);
	gtk_widget_show_all(lb_dialog);
}

void cb_click(GtkWidget *dialog) {
	GtkWidget *cb_dialog, *dialog_content;
	GtkWidget *dialog_box;

	GtkWidget *coord_box, *first_box;

	GtkWidget *description_label, *add_bttn;
	GtkWidget *first_label, *coord_label;
	GtkWidget *first_entry, *coord_entry;

	cb_dialog = gtk_dialog_new_with_buttons("circle", (GtkWindow*)NULL, (GtkDialogFlags)NULL, NULL, GTK_RESPONSE_NONE, NULL);
	dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(cb_dialog));
	g_signal_connect_swapped(cb_dialog, "response", G_CALLBACK(gtk_widget_destroy), cb_dialog);

	// init elements
	description_label = gtk_label_new("separate all data with a space, for example: 20 50");
	add_bttn = gtk_button_new_with_label("add");

	coord_label = gtk_label_new("coordinates");
	coord_entry = gtk_entry_new();

	first_label = gtk_label_new("d");
	first_entry = gtk_entry_new();

	// init boxes
	coord_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	first_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	// pack boxes
	gtk_box_pack_start(GTK_BOX(coord_box), coord_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(coord_box), coord_entry, TRUE, TRUE, 5);	

	gtk_box_pack_start(GTK_BOX(first_box), first_label, FALSE, FALSE, 5);	
	gtk_box_pack_start(GTK_BOX(first_box), first_entry, TRUE, TRUE, 5);

	// pack dialog_box
	dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), description_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), coord_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), first_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), add_bttn, TRUE, TRUE, 5);

	gtk_container_add(GTK_CONTAINER(dialog_content), dialog_box);
	gtk_widget_show_all(cb_dialog);
}

void rb_click(GtkWidget *dialog) {
	GtkWidget *rb_dialog, *dialog_content;
	GtkWidget *dialog_box;

	GtkWidget *coord_box, *first_box, *second_box;

	GtkWidget *description_label, *add_bttn;
	GtkWidget *first_label, *second_label, *coord_label;
	GtkWidget *first_entry, *second_entry, *coord_entry;
	GtkWidget *vertical_sep;

	rb_dialog = gtk_dialog_new_with_buttons("rect", (GtkWindow*)NULL, (GtkDialogFlags)NULL, NULL, GTK_RESPONSE_NONE, NULL);
	dialog_content = gtk_dialog_get_content_area(GTK_DIALOG(rb_dialog));
	g_signal_connect_swapped(rb_dialog, "response", G_CALLBACK(gtk_widget_destroy), rb_dialog);

	// init elements
	description_label = gtk_label_new("separate all data with a space, for example: 20 50");
	add_bttn = gtk_button_new_with_label("add");

	coord_label = gtk_label_new("coordinates");
	coord_entry = gtk_entry_new();

	first_label = gtk_label_new("by 2 points");
	second_label = gtk_label_new("by lenght & width");
	first_entry = gtk_entry_new();
	second_entry = gtk_entry_new();

	vertical_sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

	// init boxes
	coord_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	first_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	second_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	// pack boxes
	gtk_box_pack_start(GTK_BOX(coord_box), coord_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(coord_box), coord_entry, TRUE, TRUE, 5);	

	gtk_box_pack_start(GTK_BOX(first_box), first_label, FALSE, FALSE, 5);	
	gtk_box_pack_start(GTK_BOX(first_box), first_entry, TRUE, TRUE, 5);

	gtk_box_pack_start(GTK_BOX(second_box), second_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(second_box), second_entry, TRUE, TRUE, 5);

	// pack dialog_box
	dialog_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), description_label, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), coord_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), vertical_sep, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), first_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), second_box, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(dialog_box), add_bttn, TRUE, TRUE, 5);

	gtk_container_add(GTK_CONTAINER(dialog_content), dialog_box);
	gtk_widget_show_all(rb_dialog);
}
