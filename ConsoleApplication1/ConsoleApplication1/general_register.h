#pragma once
#include <string>
#include <cstdint>

namespace OSSim {
	class general_register {
	public:
		general_register();
		~general_register();
		uint32_t get_content();
		void set_content(uint32_t contents);
		void clear();
	private:
		uint32_t content;
	};
}
