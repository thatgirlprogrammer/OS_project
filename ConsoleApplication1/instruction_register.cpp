#include "instruction_register.h"

instruction_register::instruction_register(std::vector<std::string>* instructions1)
{
	instructions = instructions1;
}

instruction_register::~instruction_register()
{
	delete instructions;
}

std::string instruction_register::get_instruction(int index)
{
	return instructions->at(index);
}
