#include "general_register.h"

OSSim::general_register::general_register(){
	content = 0;
}

OSSim::general_register::~general_register(){}

int OSSim::general_register::get_content(){
	return content;
}

void OSSim::general_register::set_content(int contents){
	content = contents;
}

void OSSim::general_register::clear()
{
	content = 0;
}
