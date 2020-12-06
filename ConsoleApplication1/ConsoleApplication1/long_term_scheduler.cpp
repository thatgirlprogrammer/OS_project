#include "long_term_scheduler.h"

using namespace OSSim;

void long_term_scheduler::schedule() {
	if (new_q->size() > 0) {
		int size = 0;
		int i = 0;
		int k = 0;
		int start_input = 0;
		int start_output = 0;
		int start_temp = 0;

		uint8_t cache[100 * 4] = { 0 };

		PCB_info* pcb = new_q->at(i);

		while (ram->hasHole(4) && ram->freeFrame() != -1) {
			k = 0;
			int frame = ram->freeFrame();
			pcb->pc.job_memory_address = frame;
			for (int j = 0; j < pcb->pc.pages.size(); ++j) {
				int32_t data1 = dsk->read(pcb->pc.pages.at(j), 0);
				int32_t data2 = dsk->read(pcb->pc.pages.at(j), 1);
				int32_t data3 = dsk->read(pcb->pc.pages.at(j), 2);
				int32_t data4 = dsk->read(pcb->pc.pages.at(j), 3);
				
				cache[k] = data1 >> 24;
				cache[k + 1] = data1 >> 16;
				cache[k + 2] = data1 >> 8;
				cache[k + 3] = data1;

				cache[k + 4] = data2 >> 24;
				cache[k + 5] = data2 >> 16;
				cache[k + 6] = data2 >> 8;
				cache[k + 7] = data2;

				cache[k + 8] = data3 >> 24;
				cache[k + 9] = data3 >> 16;
				cache[k + 10] = data3 >> 8;
				cache[k + 11] = data3;

				cache[k + 12] = data4 >> 24;
				cache[k + 13] = data4 >> 16;
				cache[k + 14] = data4 >> 8;
				cache[k + 15] = data4;

				k += 16;
				
				if (j < 4) {
					page_t->addPage(frame, pcb->pc.job_number, pcb->pc.pages.at(j));
					pcb->pc.frames.push_back(frame);
					write_to_ram(frame, data1, data2, data3, data4);
					frame = ram->freeFrame();
					
				}
				else {
					
					for (int l = 0; l < 4; ++l) {
						int32_t data;
						if (l == 1) {
							data = data1;
						}
						else if (l == 2) {
							data = data2;
						}
						else if (l == 3) {
							data = data3;
						}
						else {
							data = data4;
						}
					}
				}
				
			}
			uint16_t l;
			uint16_t j = 0;
			uint16_t p;
			for (l = 0; l < pcb->pc.job_instruction_count * 4; l += 4) {
				
				pcb->pc.itCache[l] = cache[l];
				pcb->pc.itCache[l + 1] = cache[l + 1];
				pcb->pc.itCache[l + 2] = cache[l + 2];
				pcb->pc.itCache[l + 3] = cache[l + 3];
				
			}
			
			p = l;
			for (l = l; l < (pcb->b.input_buffer * 4) + p; l += 4) {
				
					pcb->pc.ipCache[j] = cache[l];
					pcb->pc.ipCache[j + 1] = cache[l + 1];
					pcb->pc.ipCache[j + 2] = cache[l + 2];
					pcb->pc.ipCache[j + 3] = cache[l + 3];
				j += 4;
			}
			p = l;
			j = 0;
			for (l = l; l < (pcb->b.output_buffer * 4) + p; l += 4) {
				
					pcb->pc.oCache[j] = cache[l];
					pcb->pc.oCache[j + 1] = cache[l + 1];
					pcb->pc.oCache[j + 2] = cache[l +2];
					pcb->pc.oCache[j + 3] = cache[l + 3];
	
				j += 4;
			}
			p = l;
			j = 0;
			for (l = l; l < (pcb->b.temp_buffer * 4) + p; l += 4) {
			
					pcb->pc.tempCache[j] = cache[l];
					pcb->pc.tempCache[j + 1] = cache[l + 1];
					pcb->pc.tempCache[j + 2] = cache[l + 2];
					pcb->pc.tempCache[j + 3] = cache[l + 3];
				
				j += 4;
			}
			load->move_new_ready(0);
			if (new_q->size() > 0) {
				pcb = new_q->at(0);
			}
			else {
				return;
			}
		}
	}
}
