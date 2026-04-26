#include "c74_min.h"

#include <cstdlib>
#include <string>

#ifdef _WIN32
#define setenv(name, value, overwrite) _putenv_s(name, value)
#define unsetenv(name) _putenv_s(name, "")
#endif

class bbb_utils_env : public c74::min::object<bbb_utils_env> {
public:
	MIN_DESCRIPTION{"Read and write environment variables"};
	MIN_TAGS{"env, environment, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) get/set/unset messages"};
	c74::min::outlet<> output{this, "(symbol) environment variable value"};

	c74::min::message<> get_msg{this, "get", "Get environment variable value",
		MIN_FUNCTION {
			if(args.empty()) {
				return {};
			}
			auto name = std::string(args[0]);
			auto val = std::getenv(name.c_str());
			if(val) {
				output.send(c74::min::symbol(val));
			} else {
				output.send(c74::min::symbol(""));
			}
			return {};
		}};

	c74::min::message<> set_msg{this, "set", "Set environment variable",
		MIN_FUNCTION {
			if(args.size() < 2) {
				return {};
			}
			auto name = std::string(args[0]);
			auto value = std::string(args[1]);
			::setenv(name.c_str(), value.c_str(), 1);
			return {};
		}};

	c74::min::message<> unset_msg{this, "unset", "Unset environment variable",
		MIN_FUNCTION {
			if(args.empty()) {
				return {};
			}
			auto name = std::string(args[0]);
			::unsetenv(name.c_str());
			return {};
		}};
};

MIN_EXTERNAL(bbb_utils_env);
