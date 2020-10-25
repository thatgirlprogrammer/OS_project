#pragma once
#include <vector>
#include "runnable.h"
#include "job_number.h"
#include "general_register.h"

namespace OSSim {
	class PCB_Magager {
	public:
		static void run() {
			IRunnable* pm = new job_number();
			pm->add_job(4);
			pm->add_job(0);
			pm->add_job(5);
			pm->add_job(1);
			pm->add_job(2);
			pm->run();
			pm->print_compare();

			IRunnable* pm2 = new job_number();
			pm2->add_job(4);
			pm2->add_job(0);
			pm2->add_job(5);
			pm2->add_job(1);
			pm2->add_job(2);
			pm2->run();
			pm2->print_compare();

			delete pm;
			delete pm2;
		}
	};
}
