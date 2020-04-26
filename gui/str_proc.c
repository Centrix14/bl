#include <ctype.h>

int is_empty(char *str) {
	char *sptr = str;

	while (*sptr) {
		if (!isspace((int)(*sptr))) return 0;	
		sptr++;
	}
	return 1;
}
