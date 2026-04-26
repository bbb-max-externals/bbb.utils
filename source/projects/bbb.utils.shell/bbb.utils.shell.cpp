#include "c74_min.h"
#include "bbb/process.h"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class bbb_utils_shell : public c74::min::object<bbb_utils_shell> {
public:
	MIN_DESCRIPTION{"Execute shell commands from Max"};
	MIN_TAGS{"shell, system, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) exec/run messages"};
	c74::min::outlet<> stdout_out{this, "(symbol) stdout"};
	c74::min::outlet<> stderr_out{this, "(symbol) stderr"};
	c74::min::outlet<> status_out{this, "(anything) done <code> / error <msg>"};

	c74::min::attribute<c74::min::symbol> shell_attr{
		this, "shell", c74::min::symbol("/bin/bash"),
		c74::min::description{"Path to the shell binary"}};

	c74::min::attribute<bool> async_attr{
		this, "async", true,
		c74::min::description{"Execute asynchronously"}};

	c74::min::message<> exec_msg{this, "exec", "Execute a shell command string",
		MIN_FUNCTION {
			if(m_busy.load()) {
				send_error("busy");
				return {};
			}
			auto cmd = atoms_to_string(args);
			c74::min::symbol shell_sym = shell_attr;
			std::string shell_path = shell_sym;
			if(async_attr) {
				spawn_async(shell_path, {"-c", cmd});
			} else {
				run_sync(shell_path, {"-c", cmd});
			}
			return {};
		}};

	c74::min::message<> run_msg{this, "run", "Run a shell script file",
		MIN_FUNCTION {
			if(m_busy.load()) {
				send_error("busy");
				return {};
			}
			auto path = atoms_to_string(args);
			c74::min::symbol shell_sym = shell_attr;
			std::string shell_path = shell_sym;
			if(async_attr) {
				spawn_async(shell_path, {path});
			} else {
				run_sync(shell_path, {path});
			}
			return {};
		}};

	c74::min::queue<> m_queue{this, MIN_FUNCTION {
		deliver_results();
		return {};
	}};

	~bbb_utils_shell() {
		if(m_worker.joinable()) {
			m_worker.join();
		}
	}

private:
	std::thread m_worker;
	std::atomic<bool> m_busy{false};
	bbb::process_result m_result;
	std::mutex m_result_mutex;

	void spawn_async(const std::string &shell_path,
					 const std::vector<std::string> &cmd_args) {
		m_busy.store(true);
		m_worker = std::thread([this, shell_path, cmd_args]() {
			try {
				auto result = bbb::execute(shell_path, cmd_args);
				{
					std::lock_guard<std::mutex> lock(m_result_mutex);
					m_result = std::move(result);
				}
			} catch(const std::exception &e) {
				std::lock_guard<std::mutex> lock(m_result_mutex);
				m_result = {"", e.what(), -1};
			}
			m_queue.set();
		});
	}

	void run_sync(const std::string &shell_path,
				  const std::vector<std::string> &cmd_args) {
		try {
			auto result = bbb::execute(shell_path, cmd_args);
			output_result(result);
		} catch(const std::exception &e) {
			send_error(e.what());
		}
	}

	void deliver_results() {
		if(m_worker.joinable()) {
			m_worker.join();
		}
		bbb::process_result result;
		{
			std::lock_guard<std::mutex> lock(m_result_mutex);
			result = std::move(m_result);
		}
		m_busy.store(false);
		output_result(result);
	}

	void output_result(const bbb::process_result &result) {
		c74::min::atoms status;
		status.push_back(c74::min::symbol("done"));
		status.push_back(result.exit_code);
		status_out.send(status);

		auto trimmed_err = trim(result.stderr_output);
		if(!trimmed_err.empty()) {
			stderr_out.send(c74::min::symbol(trimmed_err));
		}

		auto trimmed_out = trim(result.stdout_output);
		if(!trimmed_out.empty()) {
			stdout_out.send(c74::min::symbol(trimmed_out));
		}
	}

	void send_error(const std::string &msg) {
		c74::min::atoms err;
		err.push_back(c74::min::symbol("error"));
		err.push_back(c74::min::symbol(msg));
		status_out.send(err);
	}

	static auto atoms_to_string(const c74::min::atoms &args) -> std::string {
		std::string result;
		for(size_t i = 0; i < args.size(); ++i) {
			if(i > 0) {
				result += " ";
			}
			result += std::string(args[i]);
		}
		return result;
	}

	static auto trim(const std::string &s) -> std::string {
		auto end = s.find_last_not_of(" \t\n\r");
		if(end == std::string::npos) {
			return "";
		}
		auto start = s.find_first_not_of(" \t\n\r");
		return s.substr(start, end - start + 1);
	}
};

MIN_EXTERNAL(bbb_utils_shell);
