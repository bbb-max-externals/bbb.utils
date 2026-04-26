#include "c74_min.h"

#include <regex>
#include <string>

class bbb_utils_regex : public c74::min::object<bbb_utils_regex> {
public:
	MIN_DESCRIPTION{"Regular expression search, replace, and match"};
	MIN_TAGS{"regex, text, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) regex messages"};
	c74::min::outlet<> output{this, "(anything) match results"};

	c74::min::attribute<bool> icase_attr{
		this, "icase", false,
		c74::min::description{"Case insensitive matching"}};

	c74::min::message<> search_msg{this, "search", "Search text with pattern: search <pattern> <text...>",
		MIN_FUNCTION {
			if(args.size() < 2) return {};
			auto pattern = std::string(args[0]);
			auto text = atoms_to_string(args, 1);
			auto flags = make_flags();

			try {
				std::regex re(pattern, flags);
				std::smatch m;
				if(std::regex_search(text, m, re)) {
					output.send(c74::min::symbol(m.str()));
				} else {
					output.send(c74::min::symbol(""));
				}
			} catch(const std::regex_error &e) {
				cerr << "regex error: " << e.what() << c74::min::endl;
			}
			return {};
		}};

	c74::min::message<> replace_msg{this, "replace", "Replace matches: replace <pattern> <replacement> <text...>",
		MIN_FUNCTION {
			if(args.size() < 3) return {};
			auto pattern = std::string(args[0]);
			auto replacement = std::string(args[1]);
			auto text = atoms_to_string(args, 2);
			auto flags = make_flags();

			try {
				std::regex re(pattern, flags);
				auto result = std::regex_replace(text, re, replacement);
				output.send(c74::min::symbol(result));
			} catch(const std::regex_error &e) {
				cerr << "regex error: " << e.what() << c74::min::endl;
			}
			return {};
		}};

	c74::min::message<> match_msg{this, "match", "Test if pattern matches: match <pattern> <text...>",
		MIN_FUNCTION {
			if(args.size() < 2) return {};
			auto pattern = std::string(args[0]);
			auto text = atoms_to_string(args, 1);
			auto flags = make_flags();

			try {
				std::regex re(pattern, flags);
				bool matched = std::regex_search(text, re);
				output.send(matched ? 1 : 0);
			} catch(const std::regex_error &e) {
				cerr << "regex error: " << e.what() << c74::min::endl;
			}
			return {};
		}};

	c74::min::message<> groups_msg{this, "groups", "Extract capture groups: groups <pattern> <text...>",
		MIN_FUNCTION {
			if(args.size() < 2) return {};
			auto pattern = std::string(args[0]);
			auto text = atoms_to_string(args, 1);
			auto flags = make_flags();

			try {
				std::regex re(pattern, flags);
				std::smatch m;
				if(std::regex_search(text, m, re)) {
					c74::min::atoms result;
					for(size_t i = 1; i < m.size(); ++i) {
						result.push_back(c74::min::symbol(m[i].str()));
					}
					if(!result.empty()) {
						output.send(result);
					}
				}
			} catch(const std::regex_error &e) {
				cerr << "regex error: " << e.what() << c74::min::endl;
			}
			return {};
		}};

private:
	static auto atoms_to_string(const c74::min::atoms &args, size_t start) -> std::string {
		std::string result;
		for(size_t i = start; i < args.size(); ++i) {
			if(i > start) result += " ";
			result += std::string(args[i]);
		}
		return result;
	}

	auto make_flags() -> std::regex_constants::syntax_option_type {
		auto flags = std::regex_constants::ECMAScript;
		if(icase_attr) flags |= std::regex_constants::icase;
		return flags;
	}
};

MIN_EXTERNAL(bbb_utils_regex);
