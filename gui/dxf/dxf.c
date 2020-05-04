#include <stdio.h>
#include <stdlib.h>
#include "dxf.h"

char *dxf_file = NULL;

void dxf_err(int err_code) {
	int codes[] = {-1};
	char *msg[] = {"error opening the file"};

	for (int i = 0; i < 1; i++) {
		if (err_code == codes[i]) {
			puts(msg[i]);
			exit(err_code);
		}
	}
}

void dxf_ins_obj(char *fname, int code, char *data) {
	FILE *dxf = fopen(fname, "a");

	if (!dxf)
		dxf_err(-1);
	fprintf(dxf, "  %d\n%s\n", code, data);
	fclose(dxf);
}

void dxf_ins_var(char *fname, char *name, int vtype, char *val) {
	dxf_ins_obj(fname, DXF_VAR_NAME, name);
	dxf_ins_obj(fname, vtype, val);
}

void dxf_init(char *fname) {
	dxf_file = fname;
	dxf_ins_obj(fname, DXF_COMMENT, "ndl v0.1");
}

void dxf_end() {
	dxf_ins_obj(dxf_file, DXF_OBJ_TYPE, "EOF");
}

void dxf_start_section() {
	dxf_ins_obj(dxf_file, DXF_OBJ_TYPE, "SECTION");
}

void dxf_end_section() {
	dxf_ins_obj(dxf_file, DXF_OBJ_TYPE, "ENDSEC");
}

void dxf_start_tables() {
	dxf_ins_obj(dxf_file, DXF_NAME, "TABLES");
}
