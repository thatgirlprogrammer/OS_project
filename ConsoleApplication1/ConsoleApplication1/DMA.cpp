#include "DMA.h"

uint32_t DMA::read(uint32_t frame, int offset) {
	return memory->getMem(frame, offset);
}

void DMA::write(int frame, uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4) {
	memory->setMem(frame, d1, d2, d3, d4);
}
