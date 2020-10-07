#pragma once
#include <vector>
#include "general_register.h"

namespace OSSim {
	struct pcb {
		int job_number = 0;
		int job_priority = 0;
		int job_disk_address = 0x0;
		int job_instruction_count = 0;
		bool job_in_memory = false;
		general_register registers[16];
	};
}