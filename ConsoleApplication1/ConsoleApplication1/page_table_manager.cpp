#include "page_table_manager.h"

page_table_manager::page_table_manager() {

}

void page_table_manager::addPage(int frame, int p_id, unsigned int pg_num) {
	process_id[frame] = p_id;
	page_num[frame] = pg_num;
	valid[frame] = true;
}

int page_table_manager::getPage(int p_id, unsigned int pg_num) {
	for (int i = 0; i < 256; ++i) {
		if (process_id[i] == p_id && page_num[i] == pg_num) {
			if (pg_f->interrupt(valid[i]) == false) {
				return -1;
			}
			return i;
		}
	}
	return -1;
}
