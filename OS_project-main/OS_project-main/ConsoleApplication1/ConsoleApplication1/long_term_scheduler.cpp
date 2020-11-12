#include "long_term_scheduler.h"

using namespace OSSim;

void long_term_scheduler::schedule() {
	if (new_q->size() > 0) {
		int size = 0;
		int i = 0;
		PCB_info* pcb = new_q->at(i);

		while (ram->hasHole(pcb->pc.job_size)) {
			int frame = ram->freeFrame();
			pcb->pc.job_memory_address = frame;
			for (uint16_t j = 0; j < pcb->pc.job_size; ++j) {
				int32_t data1 = dsk->read(pcb->pc.job_disk_address + j, j);
				int32_t data2 = dsk->read(pcb->pc.job_disk_address + j, j + 1);
				int32_t data3 = dsk->read(pcb->pc.job_disk_address + j, j + 2);
				int32_t data4 = dsk->read(pcb->pc.job_disk_address + j, j + 3);
				page_t->addPage(frame, pcb->pc.job_number, pcb->pc.job_disk_address + j);
				write_to_ram(frame, data1, data2, data3, data4);
				frame = ram->freeFrame();
			}
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
