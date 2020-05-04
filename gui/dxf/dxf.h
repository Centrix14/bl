#ifndef __NORMAL_DXF_LIBRARY_DXF_H_INCLUDED__
#define __NORMAL_DXF_LIBRARY_DXF_H_INCLUDED__

#define DXF_COMMENT 999
#define DXF_OBJ_TYPE 0
#define DXF_NAME 2
#define DXF_VAR_NAME 9

#define DXF_VTYPE_TEXT 1
#define DXF_VTYPE_ENTITY_HANDLE 5
#define DXF_VTYPE_INT 70
#define DXF_VTYPE_DOUBLE 40

void dxf_ins_obj(char *fname, int code, char *data);
void dxf_ins_var(char *fname, char *name, int vtype, char *val);

void dxf_init(char *fname),
   	 dxf_end(),
	 dxf_start_section(),
	 dxf_end_section(),
	 dxf_start_header(),
	 dxf_start_tables();

#endif
