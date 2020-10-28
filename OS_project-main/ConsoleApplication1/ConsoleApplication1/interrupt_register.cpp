#include "interrupt_register.h"

interrupt_register::interrupt_register()
{
	interrupts[0] = new interrupt(*(new std::string("ctrl-C")));
}

interrupt_register::~interrupt_register()
{
}

void interrupt_register::proccess_interrupt(void(*routine)())
{
	routine();
}

