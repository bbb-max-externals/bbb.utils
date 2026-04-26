#pragma once

#include <string>
#include <vector>
#include <array>
#include <stdexcept>
#include <unistd.h>
#include <sys/wait.h>
#include <poll.h>

namespace bbb {

struct process_result {
	std::string stdout_output;
	std::string stderr_output;
	int exit_code;
};

inline auto execute(const std::string &executable,
					const std::vector<std::string> &args) -> process_result {
	std::array<int, 2> stdout_pipe{};
	std::array<int, 2> stderr_pipe{};

	if(pipe(stdout_pipe.data()) < 0) {
		throw std::runtime_error("pipe() failed for stdout");
	}
	if(pipe(stderr_pipe.data()) < 0) {
		close(stdout_pipe[0]);
		close(stdout_pipe[1]);
		throw std::runtime_error("pipe() failed for stderr");
	}

	pid_t pid = fork();
	if(pid < 0) {
		close(stdout_pipe[0]);
		close(stdout_pipe[1]);
		close(stderr_pipe[0]);
		close(stderr_pipe[1]);
		throw std::runtime_error("fork() failed");
	}

	if(pid == 0) {
		close(stdout_pipe[0]);
		close(stderr_pipe[0]);
		dup2(stdout_pipe[1], STDOUT_FILENO);
		dup2(stderr_pipe[1], STDERR_FILENO);
		close(stdout_pipe[1]);
		close(stderr_pipe[1]);

		std::vector<char *> argv;
		argv.push_back(const_cast<char *>(executable.c_str()));
		for(const auto &arg : args) {
			argv.push_back(const_cast<char *>(arg.c_str()));
		}
		argv.push_back(nullptr);

		execvp(executable.c_str(), argv.data());
		_exit(127);
	}

	close(stdout_pipe[1]);
	close(stderr_pipe[1]);

	std::string stdout_buf;
	std::string stderr_buf;
	std::array<char, 4096> buffer{};

	bool stdout_open = true;
	bool stderr_open = true;

	while(stdout_open || stderr_open) {
		std::array<struct pollfd, 2> fds{};
		int nfds = 0;

		if(stdout_open) {
			fds[nfds].fd = stdout_pipe[0];
			fds[nfds].events = POLLIN;
			fds[nfds].revents = 0;
			++nfds;
		}
		if(stderr_open) {
			fds[nfds].fd = stderr_pipe[0];
			fds[nfds].events = POLLIN;
			fds[nfds].revents = 0;
			++nfds;
		}

		if(nfds == 0) break;

		int ret = poll(fds.data(), nfds, 1000);
		if(ret < 0) break;

		int idx = 0;
		if(stdout_open) {
			if(fds[idx].revents & (POLLIN | POLLHUP)) {
				ssize_t n = read(stdout_pipe[0], buffer.data(), buffer.size());
				if(n > 0) {
					stdout_buf.append(buffer.data(), n);
				} else {
					stdout_open = false;
				}
			}
			++idx;
		}
		if(stderr_open) {
			if(fds[idx].revents & (POLLIN | POLLHUP)) {
				ssize_t n = read(stderr_pipe[0], buffer.data(), buffer.size());
				if(n > 0) {
					stderr_buf.append(buffer.data(), n);
				} else {
					stderr_open = false;
				}
			}
		}
	}

	close(stdout_pipe[0]);
	close(stderr_pipe[0]);

	int status = 0;
	waitpid(pid, &status, 0);

	int exit_code = -1;
	if(WIFEXITED(status)) {
		exit_code = WEXITSTATUS(status);
	}

	return {stdout_buf, stderr_buf, exit_code};
}

} // namespace bbb
