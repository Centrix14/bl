#ifndef __ASCII_CAD_PROTO_H_INCLUDED__
#define __ASCII_CAD_PROTO_H_INCLUDED__

#define SIZE 32

int get_brush_c();
void interpret(char*);

void reta(char*),
	 rect(char*),
	 point(char*),
	 line(char*),
	 set_brush(char*),
	 sym(char*),
	 comment(char*);

#endif
