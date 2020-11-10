#include "DMA.h"

uint32_t DMA::read(uint32_t frame, int offset) {
	//++io_number;
	return memory->getMem(frame, offset);
}

void DMA::write(uint32_t current_addr, uint32_t data) {
	//++io_number;
//	memory->setMem(current_addr, data);
}
