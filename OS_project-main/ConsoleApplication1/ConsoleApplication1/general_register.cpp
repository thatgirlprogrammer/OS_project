#include "general_register.h"

OSSim::general_register::general_register(){
	content = 0;
}

OSSim::general_register::~general_register(){}

int32_t OSSim::general_register::get_content(){
	return content;
}

void OSSim::general_register::set_content(int32_t contents){
	content = contents;
}

void OSSim::general_register::clear()
{
	content = 0;
}