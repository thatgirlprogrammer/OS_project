#include "loader.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <iomanip>

using namespace std;

loader::loader(string file_name, disk* d) {
	file.open(file_name, ios::in);
	dsk = d;
	new_q = new vector<PCB_info*>;
	ready = new vector<PCB_info*>;
	running = new vector<PCB_info*>;
	waiting = new vector<PCB_info*>;
	terminated = new vector<PCB_info*>;
}
void loader::load_file() {
	PCB_info* info = new PCB_info;
	info->ios = 0;
	if (file.is_open()) {
		string line;
		int current = 0;
		int start = 0;
		while (getline(file, line)) {
			if (line.find("JOB") != std::string::npos) {
				info = new PCB_info;
				start = current;
				//cout << "Job encountered." << "\n";
				string num1 = "0x";
				string num2 = "0x";
				string num3 = "0x";
				int i = 7;
				num1 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num1 += line[i];
					++i;
				}
				++i;
				num2 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num2 += line[i];
					++i;
				}
				++i;
				num3 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num3 += line[i];
					++i;
				}
				++i;
				int32_t job_number = strtoul(num1.c_str(), nullptr, 16);
				int32_t job_count = strtoul(num2.c_str(), nullptr, 16);
				int32_t job_priority = strtoul(num3.c_str(), nullptr, 16);
				info->pc.job_number = job_number;
				info->pc.job_priority = job_priority;
				info->pc.job_instruction_count = job_count;
				info->pc.job_disk_address = current;
				//cout << num1 << " " << num2 << " " << num3 << "\n";
			}
			else if (line.find("Data") != std::string::npos) {
				//cout << "Data encountered." << "\n";
				int i = 8;
				string num1 = "0x";
				string num2 = "0x";
				string num3 = "0x";
				num1 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num1 += line[i];
					++i;
				}
				++i;
				num2 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num2 += line[i];
					++i;
				}
				++i;
				num3 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num3 += line[i];
					++i;
				}
				++i;
				int32_t iBuffer = strtoul(num1.c_str(), nullptr, 16);
				int32_t oBuffer = strtoul(num2.c_str(), nullptr, 16);
				int32_t sBuffer = strtoul(num3.c_str(), nullptr, 16);
				info->b.input_buffer = iBuffer;
				info->b.output_buffer = oBuffer;
				info->b.temp_buffer = sBuffer;
				//cout << num1 << " " << num2 << " " << num3 << "\n";
			}
			else if (line.find("END") != std::string::npos) {
				info->pc.job_size = current - start;
				cout << current - start << endl;
				new_q->push_back(info);
				//cout << "End of file." << "\n";
			}
			else {
				if (current >= 2048) {
					cout << "Too much in disk!";
				}
				else {
					//cout << "Writing to disk" << "\n";
					int32_t number = strtoul(line.c_str(), nullptr, 16);
					dsk->write(number, current);
					++current;
					//cout << current << "\n";
				}
			}
		}
		file.close();
	}
}

static bool move_new_ready_busy = false;
void loader::move_new_ready(int index) {
	while (move_new_ready_busy)
		;
	move_new_ready_busy = true;

	PCB_info* process = new_q->at(index);
	process->enter_new = std::chrono::high_resolution_clock::now();
	new_q->erase(new_q->begin() + index);
	process->pc.process_status = READY;
	ready->push_back(process);

	move_new_ready_busy = false;
}

void loader::move_waiting_ready(int index) {
	PCB_info* process = waiting->at(index);
	waiting->erase(waiting->begin() + index);
	process->pc.process_status = RUN;
	ready->push_back(process);
}
void loader::move_running(int index) {
	PCB_info* process = ready->at(index);
	process->start = std::chrono::high_resolution_clock::now();
	ready->erase(ready->begin() + index);
	process->pc.process_status = RUN;
	running->push_back(process);
}
void loader::move_waiting(int index) {
	PCB_info* process = running->at(index);
	running->erase(running->begin() + index);
	process->pc.process_status = WAIT;
	waiting->push_back(process);
}
void loader::move_terminate(int index) {
	PCB_info* process = running->at(index);
	process->end = std::chrono::high_resolution_clock::now();
	running->erase(running->begin() + index);
	process->pc.process_status = TERMINATE;
	terminated->push_back(process);
}
