#pragma once

#include "Memory.h"
#include "page_table_manager.h"

class DMA
{
public:
	DMA(Memory* mem, page_table_manager* p) { memory = mem; page_t = p; }
	uint32_t read(uint32_t frame, int offset);
	void write(int page, int process_id, uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4);
	int get_io_number() { return io_number; };
	void setIO() { io_number = 0; };
private:
	Memory* memory;
	page_table_manager* page_t;
	int io_number = 0;
};
