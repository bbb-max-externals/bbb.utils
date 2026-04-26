#include "c74_min.h"
#include "bbb/json.hpp"

#include <string>

class bbb_utils_json : public c74::min::object<bbb_utils_json> {
public:
	MIN_DESCRIPTION{"Parse, query, and stringify JSON"};
	MIN_TAGS{"json, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) json messages"};
	c74::min::outlet<> output{this, "(anything) parsed data or JSON string"};

	c74::min::message<> parse_msg{this, "parse", "Parse JSON string and output structured data",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			try {
				auto j = nlohmann::json::parse(text);
				output_json(j);
			} catch(const nlohmann::json::parse_error &e) {
				cerr << "json parse error: " << e.what() << c74::min::endl;
			}
			return {};
		}};

	c74::min::message<> stringify_msg{this, "stringify", "Convert input to JSON string",
		MIN_FUNCTION {
			auto j = atoms_to_json(args);
			output.send(c74::min::symbol(j.dump()));
			return {};
		}};

	c74::min::message<> get_msg{this, "get", "Extract value at JSON path: get <path> <json_string>",
		MIN_FUNCTION {
			if(args.size() < 2) return {};
			auto path = std::string(args[0]);
			auto text = atoms_to_string(args, 1);
			try {
				auto j = nlohmann::json::parse(text);
				auto *current = &j;
				std::istringstream path_stream(path);
				std::string key;
				nlohmann::json resolved = j;
				while(std::getline(path_stream, key, '.')) {
					if(resolved.is_object() && resolved.contains(key)) {
						resolved = resolved[key];
					} else {
						return {};
					}
				}
				output_json(resolved);
			} catch(const nlohmann::json::exception &e) {
				cerr << "json error: " << e.what() << c74::min::endl;
			}
			return {};
		}};

	c74::min::message<> keys_msg{this, "keys", "Output keys of JSON object",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			try {
				auto j = nlohmann::json::parse(text);
				if(!j.is_object()) return {};
				c74::min::atoms result;
				for(auto it = j.begin(); it != j.end(); ++it) {
					result.push_back(c74::min::symbol(it.key()));
				}
				output.send(result);
			} catch(const nlohmann::json::parse_error &e) {
				cerr << "json parse error: " << e.what() << c74::min::endl;
			}
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

	void output_json(const nlohmann::json &j) {
		if(j.is_string()) {
			output.send(c74::min::symbol(j.get<std::string>()));
		} else if(j.is_number_integer()) {
			output.send(static_cast<int>(j));
		} else if(j.is_number_float()) {
			output.send(static_cast<double>(j));
		} else if(j.is_boolean()) {
			output.send(j.get<bool>() ? 1 : 0);
		} else if(j.is_null()) {
			output.send(c74::min::symbol("null"));
		} else if(j.is_array()) {
			c74::min::atoms result;
			for(const auto &item : j) {
				if(item.is_string()) {
					result.push_back(c74::min::symbol(item.get<std::string>()));
				} else if(item.is_number_integer()) {
					result.push_back(static_cast<int>(item));
				} else if(item.is_number_float()) {
					result.push_back(static_cast<double>(item));
				} else if(item.is_boolean()) {
					result.push_back(item.get<bool>() ? 1 : 0);
				} else if(item.is_null()) {
					result.push_back(c74::min::symbol("null"));
				} else {
					result.push_back(c74::min::symbol(item.dump()));
				}
			}
			output.send(result);
		} else if(j.is_object()) {
			output.send(c74::min::symbol(j.dump()));
		}
	}

	static auto atoms_to_json(const c74::min::atoms &args) -> nlohmann::json {
		if(args.empty()) return nlohmann::json();
		if(args.size() == 1) {
			double v = static_cast<double>(args[0]);
			auto s = std::string(args[0]);
			if(s.find_first_not_of("-.0123456789") == std::string::npos && !s.empty()) {
				if(v == static_cast<int>(v) && s.find('.') == std::string::npos) {
					return static_cast<int>(v);
				}
				return v;
			}
			return s;
		}
		nlohmann::json arr = nlohmann::json::array();
		for(const auto &a : args) {
			double v = static_cast<double>(a);
			auto s = std::string(a);
			if(s.find_first_not_of("-.0123456789") == std::string::npos && !s.empty()) {
				arr.push_back(v);
			} else {
				arr.push_back(s);
			}
		}
		return arr;
	}
};

MIN_EXTERNAL(bbb_utils_json);
