#include "long_term_scheduler.h"

using namespace OSSim;

void long_term_scheduler::schedule() {
	if (new_q->size() > 0) {
		int size = 0;
		int i = 0;
		PCB_info* pcb = new_q->at(i);

		while (page_t->hasPage(pcb->pc.job_size)) {
			uint16_t start = page_t->pageStart(pcb->pc.job_size);
			for (uint16_t j = 0; j < pcb->pc.job_size; ++j) {
				int32_t data1 = dsk->read(pcb->pc.job_disk_address + j);
				int32_t data2 = dsk->read(pcb->pc.job_disk_address + j + 1);
				int32_t data3 = dsk->read(pcb->pc.job_disk_address + j + 2);
				int32_t data4 = dsk->read(pcb->pc.job_disk_address + j + 3);
				write_to_ram(start + j, data1, data2, data3, data4);
			}
			pcb->pc.job_memory_address = start;
			load->move_new_ready(i);
			if (new_q->size() > 0) {
				pcb = new_q->at(i);
			}
			else {
				return;
			}
		}
	}
}
