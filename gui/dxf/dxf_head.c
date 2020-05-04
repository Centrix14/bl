#include "dxf.h"

extern char *dxf_file;

void dxf_start_header() {
	char *var_names[] = {"$ACADVER", "$HANDSEED", "$DIMADEC", "$DIMASZ", "$DIMAUNIT", "$DIMAZIN", "$DIMDEC", "$DIMDLI", "$DIMDSEP", "$DIMEXE"};
	char *var_value[] = {"AC1024", "FFFF", "0", "2.5", "0", "3", "4", "5.0", "46", "1.25"};
	int var_types[] = {DXF_VTYPE_TEXT, DXF_VTYPE_ENTITY_HANDLE, DXF_VTYPE_INT, DXF_VTYPE_DOUBLE, DXF_VTYPE_INT, DXF_VTYPE_INT, DXF_VTYPE_INT, DXF_VTYPE_DOUBLE, DXF_VTYPE_INT, DXF_VTYPE_DOUBLE};
	dxf_ins_obj(dxf_file, DXF_NAME, "HEADER");

	/* insert vars */
	/*dxf_ins_var(dxf_file, "$ACADVER", DXF_VTYPE_TEXT, "AC1024");
	dxf_ins_var(dxf_file, "$HANDSEED", DXF_VTYPE_ENTITY_HANDLE, "FFFF");
	dxf_ins_var(dxf_file, "$DIMADEC", DXF_VTYPE_INT, "0");
	dxf_ins_var(dxf_file, "$DIMASZ", DXF_VTYPE_DOUBLE, "2.5");
	dxf_ins_var(dxf_file, "$DIMAUNIT", DXF_VTYPE_INT, "0");
	dxf_ins_var(dxf_file, "$DIMAZIN", DXF_VTYPE_INT, "3");
	dxf_ins_var(dxf_file, "$DIMDEC", DXF_VTYPE_INT, "4");
	dxf_ins_var(dxf_file, "$DIMDLI", DXF_VTYPE_DOUBLE, "5.0");
	dxf_ins_var(dxf_file, "$DIMDSEP", DXF_VTYPE_INT, "46");*/

	for (int i = 0; i < sizeof(var_names) / sizeof(char*); i++)
		dxf_ins_var(dxf_file, var_names[i], var_types[i], var_value[i]);
}
