#include "long_term_scheduler.h"

OSSim::long_term_scheduler::long_term_scheduler()
{
}

OSSim::long_term_scheduler::~long_term_scheduler()
{
}

void OSSim::long_term_scheduler::write_to_ram(uint8_t hex, PCB_info info)
{
	ram1->store(hex, info);
}

void OSSim::long_term_scheduler::schedule()
{
}

int OSSim::long_term_scheduler::calcuate_chunk_size(int cur_disk_address, pcb pcb_val)
{
	return 0;
}
