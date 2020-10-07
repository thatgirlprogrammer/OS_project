#include "program_counter.h"

program_counter::program_counter()
{
	counter = 0;
}

program_counter::~program_counter(){}

void program_counter::update_counter()
{
	counter++;
}

int program_counter::get_counter() {
	return counter;
}
