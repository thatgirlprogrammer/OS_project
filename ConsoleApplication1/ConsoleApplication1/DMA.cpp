#include "DMA.h"

uint32_t DMA::read(uint32_t frame, int offset) {
	//++io_number;
	return memory->getMem(frame, offset);
}

void DMA::write(int page, int process_id, uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4) {
	//++io_number;
//	memory->setMem(current_addr, data);
	int frame = page_t->getPage(process_id, page);
	memory->setMem(frame, d1, d2, d3, d4);

}
