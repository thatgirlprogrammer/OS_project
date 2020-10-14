#pragma once
#include <string>
#include <cstdint>

namespace OSSim {
	class general_register {
	public:
		general_register();
		~general_register();
		int32_t get_content();
		void set_content(int32_t contents);
		void clear();
	private:
		int32_t content;
	};
}
