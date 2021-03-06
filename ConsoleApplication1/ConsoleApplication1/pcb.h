#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include <string>

namespace OSSim {
	
	enum PROCESS_STATUS {NEW, READY, WAIT, RUN, TERMINATE};

	struct data {
		int data_disk_address = 0x0;
		int data_memory_address = 0x0;
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
		unsigned int job_memory_address = 0x0;
		unsigned int job_instruction_count = 0;
		unsigned int job_size = 0;
		unsigned int my_cpu = 0;
		unsigned int page_faults = 0;
		unsigned int io_requests = 0;
		bool job_in_memory = false;
		int32_t registers[16];
		uint8_t ipCache[72 * 4] = { 0 };
		uint8_t oCache[72 * 4] = { 0 };
		uint8_t itCache[72 * 4] = { 0 };
		uint8_t tempCache[72 * 4] = { 0 };
		PROCESS_STATUS process_status = NEW;
		int program_counter = 0;
		std::vector<unsigned int> num_cpus;
		std::vector<unsigned int> pages;
		std::vector<bool> valid;
		std::vector<bool> in_mem;
		std::vector<unsigned int> frames;
		bool on_zero = false;
		bool on_one = false;
		bool on_two = false;
		bool on_three = false;
	};

	struct PCB_info {
		struct data d;
		struct buffer b;
		struct process_details pd;
		struct pcb pc;
		std::chrono::steady_clock::time_point enter_new;
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
		std::vector<std::chrono::steady_clock::time_point> waiting;
		std::string wait;
		int ios;
		unsigned int total_memory_in_use;
	};
}
