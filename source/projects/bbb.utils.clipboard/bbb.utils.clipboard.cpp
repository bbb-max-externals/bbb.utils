#include "c74_min.h"

#include <cstdio>
#include <string>

class bbb_utils_clipboard : public c74::min::object<bbb_utils_clipboard> {
public:
	MIN_DESCRIPTION{"Read and write macOS clipboard"};
	MIN_TAGS{"clipboard, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) copy/paste/clear messages"};
	c74::min::outlet<> result_out{this, "(symbol) clipboard content"};
	c74::min::outlet<> status_out{this, "(symbol) done/error"};

	c74::min::message<> copy_msg{this, "copy", "Copy text to clipboard",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			auto fp = popen("/usr/bin/pbcopy", "w");
			if(!fp) {
				status_out.send(c74::min::symbol("error"));
				return {};
			}
			fputs(text.c_str(), fp);
			pclose(fp);
			status_out.send(c74::min::symbol("done"));
			return {};
		}};

	c74::min::message<> paste_msg{this, "paste", "Read clipboard content",
		MIN_FUNCTION {
			auto fp = popen("/usr/bin/pbpaste", "r");
			if(!fp) {
				status_out.send(c74::min::symbol("error"));
				return {};
			}
			std::string result;
			char buffer[4096];
			while(auto n = fread(buffer, 1, sizeof(buffer), fp)) {
				result.append(buffer, n);
			}
			pclose(fp);
			if(!result.empty() && result.back() == '\n') {
				result.pop_back();
			}
			result_out.send(c74::min::symbol(result));
			return {};
		}};

	c74::min::message<> clear_msg{this, "clear", "Clear clipboard",
		MIN_FUNCTION {
			auto fp = popen("/usr/bin/pbcopy", "w");
			if(fp) pclose(fp);
			status_out.send(c74::min::symbol("done"));
			return {};
		}};

private:
	static auto atoms_to_string(const c74::min::atoms &args) -> std::string {
		std::string result;
		for(size_t i = 0; i < args.size(); ++i) {
			if(i > 0) result += " ";
			result += std::string(args[i]);
		}
		return result;
	}
};

MIN_EXTERNAL(bbb_utils_clipboard);
