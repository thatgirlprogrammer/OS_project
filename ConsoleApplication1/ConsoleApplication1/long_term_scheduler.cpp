#include "long_term_scheduler.h"

using namespace OSSim;

void long_term_scheduler::schedule() {
	if (new_q->size() > 0) {
		int size = 0;
		int i = 0;
		PCB_info* pcb = new_q->at(i);

		while (ram->hasHole(pcb->pc.pages.size()) && ram->freeFrame() != -1) {
			int frame = ram->freeFrame();
			pcb->pc.job_memory_address = frame;
			for (int j = 0; j < pcb->pc.pages.size(); ++j) {
				int32_t data1 = dsk->read(pcb->pc.pages.at(j), 0);
				int32_t data2 = dsk->read(pcb->pc.pages.at(j), 1);
				int32_t data3 = dsk->read(pcb->pc.pages.at(j), 2);
				int32_t data4 = dsk->read(pcb->pc.pages.at(j), 3);
				std::cout << "I got from page " << pcb->pc.pages.at(j) << " the values " << data1 << " " << data2 << " " << data3 << " " << data4 << std::endl;
				page_t->addPage(frame, pcb->pc.job_number, pcb->pc.pages.at(j));
				std::cout << "My frame number is " << frame << std::endl;
				pcb->pc.frames.push_back(frame);
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
