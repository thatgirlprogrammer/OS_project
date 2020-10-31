#include "DMA.h"

uint32_t DMA::read(uint32_t current_addr) {
	++io_number;
	return memory->getMem(current_addr);
}

void DMA::write(uint32_t current_addr, uint32_t data) {
	++io_number;
	memory->setMem(current_addr, data);
}
