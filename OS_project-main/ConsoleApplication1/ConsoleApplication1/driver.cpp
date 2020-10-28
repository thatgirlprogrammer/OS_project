#pragma once
#include "driver.h"

namespace OSSim {
	driver::driver() {
		// loader();
		while (true) {
			long_term_scheduler long_term;
			short_term_scheduler short_term;
			CPU cpu;
		}
	}
}
