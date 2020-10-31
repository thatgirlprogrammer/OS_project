#include "DMA.h"

uint32_t DMA::read(uint32_t current_addr) {
	++io_number;
	memory->getLock();
	return memory->getMem(current_addr);
	memory->releaseLock();
}

void DMA::write(uint32_t current_addr, uint32_t data) {
	++io_number;
	memory->getLock();
	memory->setMem(current_addr, data);
	memory->releaseLock();
}
