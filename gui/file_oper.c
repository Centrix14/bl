#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

char *buffer = NULL;

int get_file_size(char *fname) {
	FILE *test = fopen(fname, "r");
	struct stat buf;

	if (!test) {
		fclose(test);
		return 0;
	}
	fclose(test);

	stat(fname, &buf);
	return buf.st_size;
}

void create(char *fname) {
	buffer = malloc(get_file_size(fname));

	if (!buffer)
		perror("malloc");
}

void destroy() {
	free(buffer);
}

char *read_and_fill(char *fname) {
	FILE *src = NULL;	
	char *bptr = buffer;
	int c = 0;

	src = fopen(fname, "r");
	if (!src)
		return "file not found";
	c = fgetc(src);

	while (!feof(src)) {
		*bptr = c;
		bptr++;

		c = fgetc(src);
	}

	fclose(src);
	return buffer;
}
