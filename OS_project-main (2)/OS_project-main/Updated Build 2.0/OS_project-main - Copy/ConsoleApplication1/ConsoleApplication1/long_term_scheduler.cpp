#include "long_term_scheduler.h"

using namespace OSSim;

void long_term_scheduler::schedule() {
	if (new_q->size() > 0) {
		int size = 0;
		int i = 0;
		PCB_info* pcb = new_q->at(i);
		std::cout << pcb->pc.job_number << " is currently waiting..." << std::endl;
		while (ram->hasHole(pcb->pc.job_size)) {
			uint16_t start = ram->holeStart(pcb->pc.job_size);
			for (uint16_t j = 0; j < pcb->pc.job_size; ++j) {
				write_to_ram(start + j, dsk->read(pcb->pc.job_disk_address + j));
			}
			pcb->pc.job_memory_address = start;
			load->move_new_ready(i);
			std::cout << "The job " << pcb->pc.job_number << " has left the new queue" << std::endl;
			if (new_q->size() > 0) {
				pcb = new_q->at(i);
			}
			else {
				return;
			}
		}
	}
}
