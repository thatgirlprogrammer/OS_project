#pragma once
#include <vector>
#include <iostream>
#include "general_register.h"

namespace OSSim {
	enum PROCESS_STATUS {NEW, READY, WAIT, RUN, TERMINATE};

	struct data {
		int data_disk_address = 0x0;
		int data_memory_address = 0x0;
	};

	struct page {
		unsigned int page_starting_index = 0;
		unsigned int pages_needed = 0;
		std::vector<int> pages_allocated;
	};

	struct buffer {
		int input_buffer = 0;
		int output_buffer = 0;
		int temp_buffer = 0;
	};

	struct process_details {
		bool IO_bound = false;
		bool job_in_memory = false;
		bool has_job_ran = false;
		std::string* instructions;

	};
	struct pcb {
		unsigned int job_number = 0;
		unsigned int job_priority = 0;
		unsigned int job_disk_address = 0x0;
		unsigned int job_instruction_count = 0;
		bool job_in_memory = false;
		general_register registers[16];
		PROCESS_STATUS process_status = NEW;
	};

	struct PCB_info {
		struct data d;
		struct page p;
		struct buffer b;
		struct process_details pd;
		struct pcb pc;
	};
}
