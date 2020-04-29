#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

char *buffer = NULL;

int get_file_size(char *fname) {
	struct stat buf;

	stat(fname, &buf);
	return buf.st_size;
}

void create(char *fname) {
	buffer = malloc(get_file_size(fname));

	if (!buffer) {
		perror("malloc");
		exit(0);
	}
}

void destroy() {
	free(buffer);
}

char *read_and_fill(char *fname) {
	FILE *src = fopen(fname, "r");	
	char *bptr = buffer;
	int c = fgetc(src);

	while (!feof(src)) {
		*bptr = c;
		bptr++;

		c = fgetc(src);
	}

	fclose(src);
	return buffer;
}
