#include "c74_min.h"

#include <cstdio>
#include <string>

class bbb_utils_http : public c74::min::object<bbb_utils_http> {
public:
	MIN_DESCRIPTION{"HTTP client using curl"};
	MIN_TAGS{"http, network, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) HTTP request messages"};
	c74::min::outlet<> result_out{this, "(symbol) response body"};
	c74::min::outlet<> status_out{this, "(int) HTTP status code"};

	c74::min::message<> get_msg{this, "get", "HTTP GET request",
		MIN_FUNCTION {
			auto url = atoms_to_string(args);
			auto cmd = build_curl_cmd(url, "GET", "");
			exec_request(cmd);
			return {};
		}};

	c74::min::message<> post_msg{this, "post", "HTTP POST request",
		MIN_FUNCTION {
			auto url = atoms_to_string(args);
			auto cmd = build_curl_cmd(url, "POST", body_);
			exec_request(cmd);
			return {};
		}};

	c74::min::message<> put_msg{this, "put", "HTTP PUT request",
		MIN_FUNCTION {
			auto url = atoms_to_string(args);
			auto cmd = build_curl_cmd(url, "PUT", body_);
			exec_request(cmd);
			return {};
		}};

	c74::min::message<> delete_msg{this, "delete", "HTTP DELETE request",
		MIN_FUNCTION {
			auto url = atoms_to_string(args);
			auto cmd = build_curl_cmd(url, "DELETE", "");
			exec_request(cmd);
			return {};
		}};

	c74::min::message<> body_msg{this, "body", "Set request body for POST/PUT",
		MIN_FUNCTION {
			body_ = atoms_to_string(args);
			return {};
		}};

	c74::min::message<> header_msg{this, "header", "Add request header (e.g. header Content-Type application/json)",
		MIN_FUNCTION {
			if(args.size() >= 2) {
				auto key = std::string(args[0]);
				auto val = atoms_to_string(args);
			auto pos = val.find(' ');
				if(pos != std::string::npos) val = val.substr(pos + 1);
				headers_.push_back(key + ": " + val);
			}
			return {};
		}};

	c74::min::message<> headers_clear_msg{this, "headers_clear", "Clear all custom headers",
		MIN_FUNCTION {
			headers_.clear();
			return {};
		}};

	c74::min::attribute<c74::min::symbol> method_attr{this, "method", c74::min::symbol("get"),
		c74::min::description{"Default HTTP method"},
		c74::min::setter{MIN_FUNCTION {
			return args;
		}}};

	c74::min::attribute<c74::min::symbol> content_type{this, "content_type", c74::min::symbol("application/json"),
		c74::min::description{"Content-Type header value"}};

	c74::min::attribute<double> timeout{this, "timeout", 30.0,
		c74::min::description{"Request timeout in seconds"}};

private:
	std::string body_;
	std::vector<std::string> headers_;

	static auto atoms_to_string(const c74::min::atoms &args) -> std::string {
		std::string result;
		for(size_t i = 0; i < args.size(); ++i) {
			if(i > 0) result += " ";
			result += std::string(args[i]);
		}
		return result;
	}

	auto build_curl_cmd(const std::string &url, const std::string &method, const std::string &req_body) -> std::string {
		std::string cmd = "/usr/bin/curl -s -i";
		cmd += " -X " + method;
		cmd += " --max-time " + std::to_string(static_cast<int>(timeout_));

		auto ct = std::string(content_type.get().c_str());
		if(!ct.empty()) {
			cmd += " -H 'Content-Type: " + ct + "'";
		}

		for(const auto &h : headers_) {
			cmd += " -H '" + h + "'";
		}

		if(!req_body.empty()) {
			cmd += " -d '" + escape_shell(req_body) + "'";
		}

		cmd += " '" + escape_shell(url) + "'";
		cmd += " 2>/dev/null";
		return cmd;
	}

	void exec_request(const std::string &cmd) {
		auto fp = popen(cmd.c_str(), "r");
		if(!fp) {
			status_out.send(0);
			cerr << "failed to execute curl" << c74::min::endl;
			return;
		}

		std::string response;
		char buffer[4096];
		while(auto n = fread(buffer, 1, sizeof(buffer), fp)) {
			response.append(buffer, n);
		}
		pclose(fp);

		// Separate headers from body
		auto header_end = response.find("\r\n\r\n");
		if(header_end == std::string::npos) {
			header_end = response.find("\n\n");
			if(header_end == std::string::npos) {
				result_out.send(c74::min::symbol(response));
				status_out.send(0);
				return;
			}
			header_end += 2;
		} else {
			header_end += 4;
		}

		auto body = response.substr(header_end);

		// Extract status code from first line of headers
		auto status_line_start = response.find(' ');
		int code = 0;
		if(status_line_start != std::string::npos) {
			code = std::atoi(response.c_str() + status_line_start);
		}

		if(!body.empty() && body.back() == '\n') body.pop_back();
		if(!body.empty() && body.back() == '\r') body.pop_back();

		result_out.send(c74::min::symbol(body));
		status_out.send(code);
	}

	static auto escape_shell(const std::string &s) -> std::string {
		std::string result;
		for(auto c : s) {
			if(c == '\'') {
				result += "'\\''";
			} else {
				result += c;
			}
		}
		return result;
	}

	// Workaround: attribute getter returns the stored value via a separate member
	double timeout_{30.0};
};

MIN_EXTERNAL(bbb_utils_http);
