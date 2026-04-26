#include "c74_min.h"

#include <random>
#include <string>
#include <sstream>
#include <iomanip>

class bbb_utils_uuid : public c74::min::object<bbb_utils_uuid> {
public:
	MIN_DESCRIPTION{"Generate UUID v4 strings"};
	MIN_TAGS{"uuid, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(bang) generate UUID"};
	c74::min::outlet<> output{this, "(symbol) UUID string"};

	c74::min::message<> bang_msg{this, "bang", "Generate a UUID v4",
		MIN_FUNCTION {
			output.send(c74::min::symbol(generate_uuid()));
			return {};
		}};

	c74::min::message<> generate_msg{this, "generate", "Generate a UUID v4",
		MIN_FUNCTION {
			output.send(c74::min::symbol(generate_uuid()));
			return {};
		}};

private:
	std::random_device m_rd;

	auto generate_uuid() -> std::string {
		std::mt19937 gen(m_rd());
		std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);

		uint32_t d1 = dist(gen);
		uint32_t d2 = dist(gen) & 0xFFFF;
		d2 = (d2 & 0x0FFF) | 0x4000; // version 4
		uint32_t d3 = dist(gen) & 0xFFFF;
		d3 = (d3 & 0x3FFF) | 0x8000; // variant 1
		uint32_t d4 = dist(gen);
		uint32_t d5 = dist(gen);

		std::ostringstream ss;
		ss << std::hex << std::setfill('0');
		ss << std::setw(8) << d1 << '-';
		ss << std::setw(4) << d2 << '-';
		ss << std::setw(4) << d3 << '-';
		ss << std::setw(4) << (d4 >> 16) << '-';
		ss << std::setw(8) << (d4 & 0xFFFF);
		ss << std::setw(8) << d5;

		return ss.str();
	}
};

MIN_EXTERNAL(bbb_utils_uuid);
