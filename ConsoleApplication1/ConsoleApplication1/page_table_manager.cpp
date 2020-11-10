#include "page_table_manager.h"

page_table_manager::page_table_manager() {

}

void page_table_manager::addPage(int frame, int processID, int pageNumber) {
	page_t->addPage(frame, processID, pageNumber);
}

bool page_table_manager::hasPage(int size) {
	uint16_t current = 0;
	int hole = 0;
	while (current < 512) {
		if (page_t->getValid(current) != false) {
			hole = 0;
		}
		else {
			++hole;
		}
		if (hole >= size) {
			return true;
		}
		++current;
	}
	return false;
}

int page_table_manager::pageStart(int size) {
	int current = 0;
	int start = 0;
	int hole = 0;
	while (current < 512) {
		if (page_t->getValid(current) != false) {
			hole = 0;
			++current;
			start = current;
		}
		else {
			++hole;
		}
		if (hole >= size) {
			++current;
			return start + 1;
		}
		++current;
	}
	++current;
	return start + 1;
}