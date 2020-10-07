#pragma once
#include <string>

namespace OSSim {
	class general_register {
	public:
		general_register();
		~general_register();
		int get_content();
		void set_content(int contents);
		void clear();
	private:
		int content;
	};
}
