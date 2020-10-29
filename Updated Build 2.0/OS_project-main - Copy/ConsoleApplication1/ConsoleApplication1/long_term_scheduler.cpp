#include "long_term_scheduler.h"

using namespace OSSim;

void long_term_scheduler::schedule() {
	int size = 0;
	int i = 0;
	int k = 0;
	while (k < 5) {
		PCB_info* pcb = new_q->at(i);
		while (ram->hasHole(pcb->pc.job_size) && k < 5) {
			uint16_t start = ram->holeStart(pcb->pc.job_size);
			for (uint16_t j = 0; j < pcb->pc.job_size; ++j) {
				write_to_ram(start + j, dsk->read(pcb->pc.job_disk_address + j));
			}
			pcb->pc.job_memory_address = start;
			load->move_new_ready(i);
			new_q->erase(new_q->begin() + i);
			i = (i + 1) % new_q->size();
			pcb = new_q->at(i);
			++k;
		}
	}
}
