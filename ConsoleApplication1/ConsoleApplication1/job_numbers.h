#pragma once
#include <vector>
#include "instruction.h"
#include "pcb.h"

namespace OSSim {
	class job_numbers {
	public:
		job_numbers(PCB_info pcb_info) {
			info = pcb_info;
		}

		bool operator< (const job_numbers other) const {
			return info.pc.job_instruction_count < other.info.pc.job_instruction_count;
		}

		PCB_info get_pcb_info() {
			return info;
		}

		void set_PCB_info(pcb pc, data d, buffer b, process_details pd) {
			info.pc = pc;
			info.d = d;
			info.b = b;
			info.pd = pd;
		}
	private:
		PCB_info info;
	};
}
