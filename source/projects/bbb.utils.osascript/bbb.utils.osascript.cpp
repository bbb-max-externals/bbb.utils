#include "c74_min.h"
#include "bbb/process.h"

class bbb_utils_osascript : public c74::min::object<bbb_utils_osascript> {
public:
	MIN_DESCRIPTION{"Execute AppleScript/JXA from Max"};
	MIN_TAGS{"applescript, javascript, osascript, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) exec/run messages"};
	c74::min::outlet<> result_out{this, "(symbol) script result"};
	c74::min::outlet<> stderr_out{this, "(symbol) stderr"};
	c74::min::outlet<> status_out{this, "(anything) done / error <msg>"};

	c74::min::message<> bang_msg{this, "bang", "test",
		MIN_FUNCTION {
			result_out.send("hello");
			return {};
		}};
};

MIN_EXTERNAL(bbb_utils_osascript);
