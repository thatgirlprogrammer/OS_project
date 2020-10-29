#include <iostream>
#include <string>
#include <vector>
#include "pcb.h"
#include "Runnable.h"
#include "Instruction.h"
#include "short_term_scheduler.h"
#include "job_number.h"
#include "Disassemble.h"
#include "disk.h"
#include "loader.h"
#include "CPU.h"
#include "Memory.h"
#include "long_term_scheduler.h"
#include <algorithm>

using namespace OSSim;

enum SORT_METHOD { NUMBER, PRIORITY, LENGTH };

void print(PCB_info* info) {
	std::cout << "pcb info:" << std::endl;
	std::cout << "\tnumber: " << info->pc.job_number << std::endl;
	std::cout << "\tpriority: " << info->pc.job_priority << std::endl;
	std::cout << "\tdisk address: " << info->pc.job_disk_address << std::endl;
	std::cout << "\tinstruction count: " << info->pc.job_instruction_count << std::endl;
	std::cout << "\tin memory: " << info->pc.job_in_memory << std::endl;
	std::cout << "\tstatus: " << info->pc.process_status << std::endl;
	std::cout << "\tsize: " << info->pc.job_size << std::endl;
}

int main() {
	PCB_info info;
	std::vector<Instruction> instructions;

	uint32_t val = 0x4bd63000;
	instructions.push_back(*(new Instruction(val)));


	//	std::vector<Instruction> i;
	//	i.push_back(Instruction(0xC0500070));
	//	i.push_back(Instruction(0x4B060000));
	//	i.push_back(Instruction(0x4B010000));
	//	i.push_back(Instruction(0x4B000000));
	//	i.push_back(Instruction(0x4F0A0070));
	//	i.push_back(Instruction(0x4F0D00F0));
	//	i.push_back(Instruction(0x4C0A0004));
	//	i.push_back(Instruction(0xC0BA0000));
	//	i.push_back(Instruction(0x42BD0000));
	//	i.push_back(Instruction(0x4C0D0004));
	//	i.push_back(Instruction(0x4C060001));
	//	i.push_back(Instruction(0x10658000));
	//	i.push_back(Instruction(0x56810018));
	//	i.push_back(Instruction(0x4B060000));
	//	i.push_back(Instruction(0x4F0900F0));
	//	i.push_back(Instruction(0x43900000));
	//	i.push_back(Instruction(0x4C060001));
	//	i.push_back(Instruction(0x4C090004));
	//	i.push_back(Instruction(0x43920000));
	//	i.push_back(Instruction(0x4C060001));
	//	i.push_back(Instruction(0x4C090004));
	//	i.push_back(Instruction(0x10028000));
	//	i.push_back(Instruction(0x55810060));
	//	i.push_back(Instruction(0x04020000));
	//	i.push_back(Instruction(0x10658000));
	//	i.push_back(Instruction(0x56810048));
	//	i.push_back(Instruction(0xC10000C0));
	//	i.push_back(Instruction(0x92000000));
	//	disassemble(i);


	SORT_METHOD method = NUMBER;
	disk* dsk = new disk;
	//RAM* ram = new RAM;

	loader* load = new loader("./Program-File.txt", dsk);
	load->load_file();
	/*
	PCB_info pcbs[30];
	int priorities[30];

	switch (method) {
	case SORT_METHOD::PRIORITY: {
		job_priority j;
		for (int i = 0; i < 30; i++)
			j.add_job(pcbs[i]);
		j.sort();
		for (int i = 0; i < 30; i++) {
			pcbs[i] = j.get_pcb(i);
		}
		for (int i = 0; i < 30; i++)
			print(pcbs[i]);
	} break;
	case SORT_METHOD::LENGTH: {
		job_len j;
		for (int i = 0; i < 30; i++)
			j.add_job(pcbs[i]);
		j.sort();
		for (int i = 0; i < 30; i++) {
			pcbs[i] = j.get_pcb(i);
		}
		for (int i = 0; i < 30; i++)
			print(pcbs[i]);
	} break;
	default:
		break;
	}

	//std::sort(priorities);
	for (int i = 0; i < 30; i++)
		print(pcbs[i]);
	for (int i = 0; i < 2048; ++i) {
		std::cout << dsk->read(i) << "\n";
	}
	*/
	Memory* ram = new Memory;

	long_term_scheduler* lts = new long_term_scheduler(ram, dsk, load);
	//	short_term_scheduler* sts = new short_term_scheduler(ram);
		/*
		for (uint16_t i = 0; i < 1024 * 4; i = i + 4) {
			cout << lts->read(i) << endl;
		}*/

	lts->schedule();

	std::cout << "Printing RAM" << std::endl;
	for (uint16_t i = 0; i < 1024 * 4; i = i + 4) {
		cout << lts->read(i) << endl;
	}

	//short_term_scheduler* sts = new short_term_scheduler(mem);
	/*
	int32_t chunks[67];
	for (int i = 0; i < 67; ++i) {
		chunks[i] = lts->read(i);
	}
	for (int i = 0; i < 67; ++i) {
		sts->add_memory(i, chunks[i]);
	}
	CPU cpu(mem);
	while (!cpu.isDone())
		cpu.step();
	for (int i = 67; i < 139; ++i) {
		lts->write_to_ram(dsk->read(i), i - 67);
	}
	int32_t chunk[139 - 67];
	for (int i = 67; i < 139; ++i) {
		chunk[i - 67] = lts->read(i - 67);
	}
	for (int i = 0; i < (139 - 67); ++i) {
		sts->add_memory(i, chunk[i]);
	}
	cout << "\n";
	cpu.setDone();
	cpu.setPC();
	while (!cpu.isDone())
		cpu.step();
	for (int i = 139; i < 207; ++i) {
		lts->write_to_ram(dsk->read(i), i - 139);
	}
	int32_t chunk2[207 - 139];
	for (int i = 139; i < 207; ++i) {
		chunk2[i - 139] = lts->read(i - 139);
	}
	for (int i = 0; i < (207 - 139); ++i) {
		sts->add_memory(i, chunk2[i]);
	}
	cout << "\n";
	cpu.setDone();
	cpu.setPC();
	while (!cpu.isDone())
		cpu.step();

	for (int i = 207; i < 270; ++i) {
		lts->write_to_ram(dsk->read(i), i - 207);
	}
	int32_t chunk3[270 - 207];
	for (int i = 207; i < 270; ++i) {
		chunk3[i - 207] = lts->read(i - 207);
	}
	for (int i = 0; i < (270 - 207); ++i) {
		sts->add_memory(i, chunk3[i]);
	}
	cout << "\n";
	cpu.setDone();
	cpu.setPC();
	while (!cpu.isDone())
		cpu.step();
	for (int i = 270; i < 342; ++i) {
		lts->write_to_ram(dsk->read(i), i - 270);
	}
	int32_t chunk4[342 - 270];
	for (int i = 270; i < 342; ++i) {
		chunk4[i - 270] = lts->read(i - 270);
	}
	for (int i = 0; i < (342 - 270); ++i) {
		sts->add_memory(i, chunk4[i]);
	}
	cout << "\n";
	cpu.setDone();
	cpu.setPC();
	while (!cpu.isDone())
		cpu.step();*/



	delete dsk;
	dsk = nullptr;
	delete load;
	load = nullptr;
	//delete mem;
	//mem = nullptr;
	delete lts;
	lts = nullptr;
	return 0;
}
