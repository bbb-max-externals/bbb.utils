#include "c74_min.h"
#include "bbb/process.h"

#include <string>

class bbb_utils_notify : public c74::min::object<bbb_utils_notify> {
public:
	MIN_DESCRIPTION{"Send macOS notifications"};
	MIN_TAGS{"notification, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) notify messages"};
	c74::min::outlet<> status_out{this, "(symbol) done/error"};

	c74::min::attribute<c74::min::symbol> title_attr{
		this, "title", c74::min::symbol("bbb.utils.notify"),
		c74::min::description{"Default notification title"}};

	c74::min::attribute<c74::min::symbol> sound_attr{
		this, "sound", c74::min::symbol(""),
		c74::min::description{"Notification sound name (empty = silent)"}};

	c74::min::message<> bang_msg{this, "bang", "Send notification with default title/message",
		MIN_FUNCTION {
			c74::min::symbol title_sym = title_attr;
			auto title = std::string(title_sym);
			c74::min::symbol sound_sym = sound_attr;
			auto msg = std::string(sound_sym); // no default message, just title
			send_notification(title, "");
			return {};
		}};

	c74::min::message<> notify_msg{this, "notify", "Send notification: notify <title> <message...>",
		MIN_FUNCTION {
			if(args.empty()) return {};
			auto title = std::string(args[0]);
			auto message = atoms_to_string(args, 1);
			send_notification(title, message);
			return {};
		}};

private:
	void send_notification(const std::string &title, const std::string &message) {
		std::string script = "display notification \"";
		script += escape_quotes(message);
		script += "\" with title \"";
		script += escape_quotes(title);
		script += "\"";

		c74::min::symbol sound_sym = sound_attr;
		auto sound = std::string(sound_sym);
		if(!sound.empty()) {
			script += " sound name \"";
			script += escape_quotes(sound);
			script += "\"";
		}

		auto result = bbb::execute("/usr/bin/osascript", {"-e", script});
		if(result.exit_code == 0) {
			status_out.send(c74::min::symbol("done"));
		} else {
			status_out.send(c74::min::symbol("error"));
		}
	}

	static auto atoms_to_string(const c74::min::atoms &args, size_t start) -> std::string {
		std::string result;
		for(size_t i = start; i < args.size(); ++i) {
			if(i > start) result += " ";
			result += std::string(args[i]);
		}
		return result;
	}

	static auto escape_quotes(const std::string &s) -> std::string {
		std::string result;
		result.reserve(s.size());
		for(char c : s) {
			if(c == '"') result += '\\';
			result += c;
		}
		return result;
	}
};

MIN_EXTERNAL(bbb_utils_notify);
