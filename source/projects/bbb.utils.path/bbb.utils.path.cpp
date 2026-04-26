#include "c74_min.h"

#include <cstdio>
#include <string>

#ifdef _WIN32
static const char SEP = '\\';
#else
static const char SEP = '/';
#endif

class bbb_utils_path : public c74::min::object<bbb_utils_path> {
public:
	MIN_DESCRIPTION{"Path utilities: resolve, join, basename, dirname"};
	MIN_TAGS{"path, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) path messages"};
	c74::min::outlet<> output{this, "(symbol) resolved path"};

	c74::min::message<> resolve_msg{this, "resolve", "Resolve path relative to patcher directory",
		MIN_FUNCTION {
			auto relative = atoms_to_string(args);
			auto patcher_dir = get_patcher_directory();
			if(patcher_dir.empty()) {
				cerr << "patcher not saved" << c74::min::endl;
				return {};
			}
			auto resolved = join_path(patcher_dir, relative);
			output.send(c74::min::symbol(resolved));
			return {};
		}};

	c74::min::message<> absolute_msg{this, "absolute", "Check if path is absolute: output 1 or 0",
		MIN_FUNCTION {
			auto p = atoms_to_string(args);
			output.send((!p.empty() && (p[0] == '/' || p[0] == SEP)) ? 1 : 0);
			return {};
		}};

	c74::min::message<> basename_msg{this, "basename", "Output filename part of path",
		MIN_FUNCTION {
			auto p = atoms_to_string(args);
			auto pos = p.find_last_of("/\\");
			if(pos == std::string::npos) {
				output.send(c74::min::symbol(p));
			} else {
				output.send(c74::min::symbol(p.substr(pos + 1)));
			}
			return {};
		}};

	c74::min::message<> dirname_msg{this, "dirname", "Output directory part of path",
		MIN_FUNCTION {
			auto p = atoms_to_string(args);
			auto pos = p.find_last_of("/\\");
			if(pos == std::string::npos) {
				output.send(c74::min::symbol("."));
			} else if(pos == 0) {
				output.send(c74::min::symbol("/"));
			} else {
				output.send(c74::min::symbol(p.substr(0, pos)));
			}
			return {};
		}};

	c74::min::message<> join_msg{this, "join", "Join two path components: join <path1> <path2>",
		MIN_FUNCTION {
			if(args.size() < 2) return {};
			auto p1 = std::string(args[0]);
			auto p2 = std::string(args[1]);
			output.send(c74::min::symbol(join_path(p1, p2)));
			return {};
		}};

	c74::min::message<> exists_msg{this, "exists", "Check if path exists: output 1 or 0",
		MIN_FUNCTION {
			auto p = atoms_to_string(args);
			FILE *f = std::fopen(p.c_str(), "r");
			if(f) {
				std::fclose(f);
				output.send(1);
			} else {
				output.send(0);
			}
			return {};
		}};

	c74::min::message<> expand_msg{this, "expand", "Expand tilde (~) to home directory",
		MIN_FUNCTION {
			auto p = atoms_to_string(args);
			if(!p.empty() && p[0] == '~') {
#ifdef _WIN32
				auto home = std::getenv("USERPROFILE");
#else
				auto home = std::getenv("HOME");
#endif
				if(home) {
					p = std::string(home) + p.substr(1);
				}
			}
			output.send(c74::min::symbol(p));
			return {};
		}};

private:
	auto get_patcher_directory() -> std::string {
		auto max_obj = this->maxobj();
		auto patcher = c74::max::object_attr_getobj(max_obj, c74::max::gensym("patcher"));
		if(!patcher) return "";

		auto filepath = c74::max::object_attr_getsym(patcher, c74::max::gensym("filepath"));
		if(!filepath || !filepath->s_name[0]) return "";

		auto p = std::string(filepath->s_name);
		auto pos = p.find_last_of("/\\");
		if(pos == std::string::npos) return "";
		return p.substr(0, pos);
	}

	static auto join_path(const std::string &base, const std::string &relative) -> std::string {
		if(relative.empty()) return base;
		if(relative[0] == '/' || relative[0] == SEP) return relative;
		if(base.empty()) return relative;
		if(base.back() == SEP) return base + relative;
		return base + SEP + relative;
	}

	static auto atoms_to_string(const c74::min::atoms &args) -> std::string {
		std::string result;
		for(size_t i = 0; i < args.size(); ++i) {
			if(i > 0) result += " ";
			result += std::string(args[i]);
		}
		return result;
	}
};

MIN_EXTERNAL(bbb_utils_path);
