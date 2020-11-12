#pragma once

#include "Memory.h"

class DMA
{
public:
	DMA(Memory* mem) { memory = mem; }
	uint32_t read(uint32_t frame, int offset);
	void write(uint32_t current_addr, uint32_t data);
	int get_io_number() { return io_number; };
	void setIO() { io_number = 0; };
private:
	Memory* memory;
	int io_number = 0;
};
