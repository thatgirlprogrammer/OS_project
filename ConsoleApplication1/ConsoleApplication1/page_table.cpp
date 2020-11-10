#include "page_table.h"

void page_table::addPage(int frame, int processID, int pageNumber) {
	process[frame] = processID;
	page[frame] = pageNumber;
	valid[frame] = true;
}

int page_table::getFrame(int processID, int pageNumber) {
	for (int i = 0; i < 512; ++i) {
		if (process[i] == processID && page[i] == pageNumber) {
			if (valid[i] == true) {
				return i;
			}
			else {
				//trigger an interrupt
			}
		}
	}
}

bool page_table::getValid(int frame) {
	return valid[frame];
}