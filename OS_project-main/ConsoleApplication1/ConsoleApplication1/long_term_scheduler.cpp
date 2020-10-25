#include "long_term_scheduler.h"

OSSim::long_term_scheduler::long_term_scheduler()
{
}

OSSim::long_term_scheduler::~long_term_scheduler()
{
}

void OSSim::long_term_scheduler::write_to_ram(vector<Instruction>* hex, PCB_info info)
{
	ram1->store(hex, info);
}

