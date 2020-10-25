#pragma once
#include "interrupt.h"
#include "cstring"
#include <iostream>

class interrupt_register
{
public:
	interrupt_register();
	~interrupt_register();
	void proccess_interrupt(void (*routine)());
private:
	interrupt* interrupts[1];
};

