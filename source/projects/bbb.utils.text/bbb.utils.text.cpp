#include "c74_min.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

class bbb_utils_text : public c74::min::object<bbb_utils_text> {
public:
	MIN_DESCRIPTION{"String manipulation utilities"};
	MIN_TAGS{"text, string, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) text messages"};
	c74::min::outlet<> output{this, "(anything) result"};

	c74::min::message<> split_msg{this, "split", "Split text by delimiter (split <delimiter> <text>)",
		MIN_FUNCTION {
			if(args.size() < 2) return {};
			auto delim = std::string(args[0]);
			auto text = atoms_to_string(args, 1);
			auto parts = split_str(text, delim);
			c74::min::atoms result;
			for(const auto &p : parts) {
				result.push_back(c74::min::symbol(p));
			}
			output.send(result);
			return {};
		}};

	c74::min::message<> join_msg{this, "join", "Join atoms with delimiter (join <delimiter> <atoms...>)",
		MIN_FUNCTION {
			if(args.empty()) return {};
			auto delim = std::string(args[0]);
			std::string result;
			for(size_t i = 1; i < args.size(); ++i) {
				if(i > 1) result += delim;
				result += std::string(args[i]);
			}
			output.send(c74::min::symbol(result));
			return {};
		}};

	c74::min::message<> trim_msg{this, "trim", "Trim whitespace from text",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			auto result = trim_str(text);
			output.send(c74::min::symbol(result));
			return {};
		}};

	c74::min::message<> replace_msg{this, "replace", "Replace occurrences (replace <from> <to> <text>)",
		MIN_FUNCTION {
			if(args.size() < 3) return {};
			auto from = std::string(args[0]);
			auto to = std::string(args[1]);
			auto text = atoms_to_string(args, 2);
			if(from.empty()) { output.send(c74::min::symbol(text)); return {}; }
			size_t pos = 0;
			std::string result = text;
			while((pos = result.find(from, pos)) != std::string::npos) {
				result.replace(pos, from.size(), to);
				pos += to.size();
			}
			output.send(c74::min::symbol(result));
			return {};
		}};

	c74::min::message<> upper_msg{this, "upper", "Convert text to uppercase",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			std::transform(text.begin(), text.end(), text.begin(),
				[](unsigned char c) { return std::toupper(c); });
			output.send(c74::min::symbol(text));
			return {};
		}};

	c74::min::message<> lower_msg{this, "lower", "Convert text to lowercase",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			std::transform(text.begin(), text.end(), text.begin(),
				[](unsigned char c) { return std::tolower(c); });
			output.send(c74::min::symbol(text));
			return {};
		}};

	c74::min::message<> length_msg{this, "length", "Get text length",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			output.send(static_cast<int>(text.size()));
			return {};
		}};

	c74::min::message<> pad_msg{this, "pad", "Pad text to length (pad <char> <length> <text>)",
		MIN_FUNCTION {
			if(args.size() < 3) return {};
			auto pad_char = std::string(args[0]);
			auto target_len = static_cast<size_t>(int(args[1]));
			auto text = atoms_to_string(args, 2);
			if(text.size() < target_len) {
				text = text + std::string(target_len - text.size(), pad_char.empty() ? ' ' : pad_char[0]);
			}
			output.send(c74::min::symbol(text));
			return {};
		}};

	c74::min::message<> pad_left_msg{this, "pad_left", "Left-pad text to length (pad_left <char> <length> <text>)",
		MIN_FUNCTION {
			if(args.size() < 3) return {};
			auto pad_char = std::string(args[0]);
			auto target_len = static_cast<size_t>(int(args[1]));
			auto text = atoms_to_string(args, 2);
			if(text.size() < target_len) {
				text = std::string(target_len - text.size(), pad_char.empty() ? ' ' : pad_char[0]) + text;
			}
			output.send(c74::min::symbol(text));
			return {};
		}};

private:
	static auto atoms_to_string(const c74::min::atoms &args, size_t start = 0) -> std::string {
		std::string result;
		for(size_t i = start; i < args.size(); ++i) {
			if(i > start) result += " ";
			result += std::string(args[i]);
		}
		return result;
	}

	static auto split_str(const std::string &text, const std::string &delim) -> std::vector<std::string> {
		std::vector<std::string> parts;
		if(delim.empty()) {
			for(auto c : text) parts.emplace_back(1, c);
			return parts;
		}
		size_t start = 0, end;
		while((end = text.find(delim, start)) != std::string::npos) {
			parts.push_back(text.substr(start, end - start));
			start = end + delim.size();
		}
		parts.push_back(text.substr(start));
		return parts;
	}

	static auto trim_str(const std::string &s) -> std::string {
		auto start = s.find_first_not_of(" \t\r\n");
		if(start == std::string::npos) return "";
		auto end = s.find_last_not_of(" \t\r\n");
		return s.substr(start, end - start + 1);
	}
};

MIN_EXTERNAL(bbb_utils_text);
