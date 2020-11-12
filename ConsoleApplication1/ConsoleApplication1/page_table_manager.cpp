#include "page_table_manager.h"

page_table_manager::page_table_manager() {

}

void page_table_manager::addPage(int frame, int p_id, int pg_num) {
	process_id[frame] = p_id;
	page_num[frame] = pg_num;
}

int page_table_manager::getPage(int p_id, int pg_num) {

}