#include "short_term_scheduler.h"

void short_term_scheduler::schedule(int cpu_number, loader* ld) {
	if (load->get_waiting()->size() > 0) {
		PCB_info* process = load->get_waiting()->at(0);
		cpus->at(cpu_number)->reset_valid();
		bool found = true;
		for (int i = 0; i < process->pc.valid.size(); ++i) {
			if (process->pc.valid.at(i) == true && process->pc.in_mem.at(i) == false) {
				if (mem->hasHole(1)) {
					int32_t data1;
					int32_t data2;
					int32_t data3;
					int32_t data4;
					found = true;
					if (i * 4 < process->pc.job_instruction_count) {
						data1 = (int)process->pc.itCache[i * 16] << 24;
						data1 |= (int)process->pc.itCache[(i * 16) + 1] << 16;
						data1 |= (int)process->pc.itCache[(i * 16) + 2] << 8;
						data1 |= (int)process->pc.itCache[(i * 16) + 3];

						data2 = (int)process->pc.itCache[(i * 16) + 4] << 24;
						data2 |= (int)process->pc.itCache[(i * 16) + 5] << 16;
						data2 |= (int)process->pc.itCache[(i * 16) + 6] << 8;
						data2 |= (int)process->pc.itCache[(i * 16) + 7];

						data3 = (int)process->pc.itCache[(i * 16) + 8] << 24;
						data3 |= (int)process->pc.itCache[(i * 16) + 9] << 16;
						data3 |= (int)process->pc.itCache[(i * 16) + 10] << 8;
						data3 |= (int)process->pc.itCache[(i * 16) + 11];

						data4 = (int)process->pc.itCache[(i * 16) + 12] << 24;
						data4 |= (int)process->pc.itCache[(i * 16) + 13] << 16;
						data4 |= (int)process->pc.itCache[(i * 16) + 14] << 8;
						data4 |= (int)process->pc.itCache[(i * 16) + 15];
					}
					else if (i * 4 < process->pc.job_instruction_count + process->b.input_buffer) {
						data1 = (int)process->pc.ipCache[i * 16] << 24;
						data1 |= (int)process->pc.ipCache[(i * 16) + 1] << 16;
						data1 |= (int)process->pc.ipCache[(i * 16) + 2] << 8;
						data1 |= (int)process->pc.ipCache[(i * 16) + 3];

						data2 = (int)process->pc.ipCache[(i * 16) + 4] << 24;
						data2 |= (int)process->pc.ipCache[(i * 16) + 5] << 16;
						data2 |= (int)process->pc.ipCache[(i * 16) + 6] << 8;
						data2 |= (int)process->pc.ipCache[(i * 16) + 7];

						data3 = (int)process->pc.ipCache[(i * 16) + 8] << 24;
						data3 |= (int)process->pc.ipCache[(i * 16) + 9] << 16;
						data3 |= (int)process->pc.ipCache[(i * 16) + 10] << 8;
						data3 |= (int)process->pc.ipCache[(i * 16) + 11];

						data4 = (int)process->pc.ipCache[(i * 16) + 12] << 24;
						data4 |= (int)process->pc.ipCache[(i * 16) + 13] << 16;
						data4 |= (int)process->pc.ipCache[(i * 16) + 14] << 8;
						data4 |= (int)process->pc.ipCache[(i * 16) + 15];
					}
					else if (i * 4 < process->pc.job_instruction_count + process->b.input_buffer + process->b.output_buffer) {
						data1 = (int)process->pc.oCache[i * 16] << 24;
						data1 |= (int)process->pc.oCache[(i * 16) + 1] << 16;
						data1 |= (int)process->pc.oCache[(i * 16) + 2] << 8;
						data1 |= (int)process->pc.oCache[(i * 16) + 3];

						data2 = (int)process->pc.oCache[(i * 16) + 4] << 24;
						data2 |= (int)process->pc.oCache[(i * 16) + 5] << 16;
						data2 |= (int)process->pc.oCache[(i * 16) + 6] << 8;
						data2 |= (int)process->pc.oCache[(i * 16) + 7];

						data3 = (int)process->pc.oCache[(i * 16) + 8] << 24;
						data3 |= (int)process->pc.oCache[(i * 16) + 9] << 16;
						data3 |= (int)process->pc.oCache[(i * 16) + 10] << 8;
						data3 |= (int)process->pc.oCache[(i * 16) + 11];

						data4 = (int)process->pc.oCache[(i * 16) + 12] << 24;
						data4 |= (int)process->pc.oCache[(i * 16) + 13] << 16;
						data4 |= (int)process->pc.oCache[(i * 16) + 14] << 8;
						data4 |= (int)process->pc.oCache[(i * 16) + 15];
					}
					else {
						data1 = (int)process->pc.tempCache[i * 16] << 24;
						data1 |= (int)process->pc.tempCache[(i * 16) + 1] << 16;
						data1 |= (int)process->pc.tempCache[(i * 16) + 2] << 8;
						data1 |= (int)process->pc.tempCache[(i * 16) + 3];

						data2 = (int)process->pc.tempCache[(i * 16) + 4] << 24;
						data2 |= (int)process->pc.tempCache[(i * 16) + 5] << 16;
						data2 |= (int)process->pc.tempCache[(i * 16) + 6] << 8;
						data2 |= (int)process->pc.tempCache[(i * 16) + 7];

						data3 = (int)process->pc.tempCache[(i * 16) + 8] << 24;
						data3 |= (int)process->pc.tempCache[(i * 16) + 9] << 16;
						data3 |= (int)process->pc.tempCache[(i * 16) + 10] << 8;
						data3 |= (int)process->pc.tempCache[(i * 16) + 11];

						data4 = (int)process->pc.tempCache[(i * 16) + 12] << 24;
						data4 |= (int)process->pc.tempCache[(i * 16) + 13] << 16;
						data4 |= (int)process->pc.tempCache[(i * 16) + 14] << 8;
						data4 |= (int)process->pc.tempCache[(i * 16) + 15];
					}
					process->pc.in_mem.at(i) = true;
					int index = mem->freeFrame();
					page_t->addPage(index, process->pc.job_number, process->pc.pages.at(i));
					process->pc.frames.push_back(index);
					mem->setMem(index, data1, data2, data3, data4);
				}
				else {
					found = false;
				}
			}
		}
		if (found) {
			process->pc.num_cpus.push_back(cpu_number);
			load->move_waiting_running(process);
			process->pc.process_status = WAIT;
			int j;
			int i = 0;
			int p;

			int index = 0;
			bool val = process->pc.valid.at(index);

			for (j = 0; j < process->pc.job_instruction_count * 4; j += 4) {
				if (j % 16 == 0 && j != 0) {
					++index;
					val = process->pc.valid.at(index);
				}
				if (val) {
					cpus->at(cpu_number)->writeOneCache(j, process->pc.itCache[j]);
					cpus->at(cpu_number)->writeOneCache(j + 1, process->pc.itCache[j + 1]);
					cpus->at(cpu_number)->writeOneCache(j + 2, process->pc.itCache[j + 2]);
					cpus->at(cpu_number)->writeOneCache(j + 3, process->pc.itCache[j + 3]);
					cpus->at(cpu_number)->set_valid(j, true);
					cpus->at(cpu_number)->set_valid(j + 1, true);
					cpus->at(cpu_number)->set_valid(j + 2, true);
					cpus->at(cpu_number)->set_valid(j + 3, true);
				}
				
			}
			p = j;
			for (j = j; j < (process->b.input_buffer * 4) + p; j += 4) {
				if (j % 16 == 0) {
					++index;
					val = process->pc.valid.at(index);
				}
				if (val) {
					cpus->at(cpu_number)->writeOneCache(j, process->pc.ipCache[i]);
					cpus->at(cpu_number)->writeOneCache(j + 1, process->pc.ipCache[i + 1]);
					cpus->at(cpu_number)->writeOneCache(j + 2, process->pc.ipCache[i + 2]);
					cpus->at(cpu_number)->writeOneCache(j + 3, process->pc.ipCache[i + 3]);
					cpus->at(cpu_number)->set_valid(j, true);
					cpus->at(cpu_number)->set_valid(j + 1, true);
					cpus->at(cpu_number)->set_valid(j + 2, true);
					cpus->at(cpu_number)->set_valid(j + 3, true);
				}
				i += 4;
			}
			i = 0;
			p = j;
			for (j = j; j < (process->b.output_buffer * 4) + p; j += 4) {
				if (j % 16 == 0) {
					++index;
					val = process->pc.valid.at(index);
				}
				if (val) {
					cpus->at(cpu_number)->writeOneCache(j, process->pc.oCache[i]);
					cpus->at(cpu_number)->writeOneCache(j + 1, process->pc.oCache[i + 1]);
					cpus->at(cpu_number)->writeOneCache(j + 2, process->pc.oCache[i + 2]);
					cpus->at(cpu_number)->writeOneCache(j + 3, process->pc.oCache[i + 3]);
					cpus->at(cpu_number)->set_valid(j, true);
					cpus->at(cpu_number)->set_valid(j + 1, true);
					cpus->at(cpu_number)->set_valid(j + 2, true);
					cpus->at(cpu_number)->set_valid(j + 3, true);
				}
				i += 4;
			}
			i = 0;
			p = j;
			for (j = j; j < (process->b.temp_buffer * 4) + p; j += 4) {
				if (j % 16 == 0) {
					++index;
					if (index < process->pc.pages.size()) {
						val = process->pc.valid.at(index);
					}
				}
				if (val) {
					cpus->at(cpu_number)->writeOneCache(j, process->pc.tempCache[i]);
					cpus->at(cpu_number)->writeOneCache(j + 1, process->pc.tempCache[i + 1]);
					cpus->at(cpu_number)->writeOneCache(j + 2, process->pc.tempCache[i + 2]);
					cpus->at(cpu_number)->writeOneCache(j + 3, process->pc.tempCache[i + 3]);
					cpus->at(cpu_number)->set_valid(j, true);
					cpus->at(cpu_number)->set_valid(j + 1, true);
					cpus->at(cpu_number)->set_valid(j + 2, true);
					cpus->at(cpu_number)->set_valid(j + 3, true);
				}
				i += 4;
				
			}
			uint8_t l;
			for (l = 0; l < 16; ++l) {
				cpus->at(cpu_number)->writeRegisters(l, process->pc.registers[l]);
			}
			cpus->at(cpu_number)->setValuePC(process->pc.program_counter - 4);
			cpus->at(cpu_number)->set_running(process);
			cpus->at(cpu_number)->setDone();
			return;
		}
	}
	if (ld->get_ready()->size() > 0) {
		PCB_info* process = ld->get_ready()->at(0);
		cpus->at(cpu_number)->reset_valid();
		vector<unsigned int> vec = process->pc.pages;
		int16_t j = 0;
		for (int i = 0; i < 4; ++i) {
			int frame = page_t->getPage(process->pc.job_number, process->pc.pages.at(i));
			cpus->at(cpu_number)->set_valid(j, true);
			cpus->at(cpu_number)->set_valid(j + 1, true);
			cpus->at(cpu_number)->set_valid(j + 2, true);
			cpus->at(cpu_number)->set_valid(j + 3, true);
			cpus->at(cpu_number)->writeCache(j, mem->getMem(frame, 0));
			cpus->at(cpu_number)->set_valid(j + 4, true);
			cpus->at(cpu_number)->set_valid(j + 5, true);
			cpus->at(cpu_number)->set_valid(j + 6, true);
			cpus->at(cpu_number)->set_valid(j + 7, true);
			cpus->at(cpu_number)->writeCache(j + 4, mem->getMem(frame, 1));
			cpus->at(cpu_number)->set_valid(j + 8, true);
			cpus->at(cpu_number)->set_valid(j + 9, true);
			cpus->at(cpu_number)->set_valid(j + 10, true);
			cpus->at(cpu_number)->set_valid(j + 11, true);
			cpus->at(cpu_number)->writeCache(j + 8, mem->getMem(frame, 2));
			cpus->at(cpu_number)->set_valid(j + 12, true);
			cpus->at(cpu_number)->set_valid(j + 13, true);
			cpus->at(cpu_number)->set_valid(j + 14, true);
			cpus->at(cpu_number)->set_valid(j + 15, true);
			cpus->at(cpu_number)->writeCache(j + 12, mem->getMem(frame, 3));
			j += 16;
		}
		process->pc.my_cpu = cpu_number;
		process->pc.num_cpus.push_back(cpu_number);
		cpus->at(cpu_number)->set_running(process);
		cpus->at(cpu_number)->setDone();
		cpus->at(cpu_number)->setPC();
		load->move_running(process);
	}
}