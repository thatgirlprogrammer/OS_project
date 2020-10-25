#pragma once
#include <vector>
#include "instruction.h"
#include "pcb.h"

namespace OSSim {
	class priorities {
	public:
		priorities(PCB_info pcb_info, std::vector<Instruction>* instructions1) {
			info = pcb_info;
			instructions = instructions1;
		}

		bool operator< (const priorities other) const {
			return info.pc.job_priority < other.info.pc.job_priority;
		}

		PCB_info get_pcb_info() {
			return info;
		}

		void set_PCB_info(pcb pc, data d, page p, buffer b, process_details pd) {
			info.pc = pc;
			info.d = d;
			info.b = b;
			info.p = p;
			info.pd = pd;
		}

		const char* decode_istructions() { return ""; }
		void execute_instrustions() {}
	private:
		PCB_info info;
		std::vector<Instruction>* instructions;
	};
}

