#include <stddef.h>

char *fname = NULL;

void set_fname(char *new) {
	fname = new;
}

char *get_fname() {
	return fname;
}
