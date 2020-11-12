#pragma once
#include <vector>
#include "pcb.h"
#include "Memory.h"
#include "disk.h"
#include "loader.h"
#include "page_table_manager.h"

namespace OSSim
{
	class long_term_scheduler
	{
	public:
		long_term_scheduler(Memory* memory, disk* dk, loader* ld, page_table_manager* page) {
			page_t = page;
			ram = memory;
			dsk = dk;
			load = ld;
			new_q = load->get_new_q();
			ready = load->get_ready();
		}
		void write_to_ram(int index, int32_t data1, int32_t data2, int32_t data3, int32_t data4) {
			ram->setMem(index, data1, data2, data3, data4);
		}
		int32_t read(int index, int offset) {
			return ram->getMem(index, offset);
		}
		void schedule();
	private:
		Memory* ram;
		disk* dsk;
		loader* load;
		page_table_manager* page_t;
		vector<PCB_info*>* new_q;
		vector<PCB_info*>* ready;
	};
}
