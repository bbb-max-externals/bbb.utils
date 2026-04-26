#include "c74_min.h"

#include <CoreServices/CoreServices.h>
#include <atomic>
#include <mutex>
#include <string>
#include <thread>

class bbb_utils_filewatch : public c74::min::object<bbb_utils_filewatch> {
public:
	MIN_DESCRIPTION{"Watch files and directories for changes"};
	MIN_TAGS{"filewatch, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) watch/stop messages"};
	c74::min::outlet<> changed_out{this, "(symbol) changed file path"};
	c74::min::outlet<> status_out{this, "(symbol) status messages"};

	c74::min::attribute<c74::min::symbol> path_attr{
		this, "path", c74::min::symbol(""),
		c74::min::description{"Path to watch"}};

	c74::min::attribute<double> latency_attr{
		this, "latency", 0.5,
		c74::min::description{"FSEvents latency in seconds"}};

	c74::min::message<> watch_msg{this, "watch", "Start watching a path",
		MIN_FUNCTION {
			c74::min::symbol path_sym = path_attr;
			auto path = args.empty() ? std::string(path_sym) : std::string(args[0]);
			if(path.empty()) {
				cerr << "no path specified" << c74::min::endl;
				return {};
			}
			stop_watching();
			start_watching(path);
			return {};
		}};

	c74::min::message<> stop_msg{this, "stop", "Stop watching",
		MIN_FUNCTION {
			stop_watching();
			return {};
		}};

	c74::min::message<> bang_msg{this, "bang", "Start watching the @path attribute",
		MIN_FUNCTION {
			c74::min::symbol path_sym = path_attr;
			auto path = std::string(path_sym);
			if(path.empty()) {
				cerr << "no path specified" << c74::min::endl;
				return {};
			}
			stop_watching();
			start_watching(path);
			return {};
		}};

	c74::min::queue<> m_queue{this, MIN_FUNCTION {
		deliver_changes();
		return {};
	}};

	~bbb_utils_filewatch() {
		stop_watching();
	}

private:
	std::thread m_thread;
	std::atomic<bool> m_running{false};
	CFRunLoopRef m_run_loop{nullptr};
	FSEventStreamRef m_stream{nullptr};
	std::mutex m_changes_mutex;
	std::vector<std::string> m_pending_changes;

	void start_watching(const std::string &path) {
		m_running.store(true);
		m_thread = std::thread([this, path]() {
			m_run_loop = CFRunLoopGetCurrent();

			CFStringRef cf_path = CFStringCreateWithCString(kCFAllocatorDefault, path.c_str(), kCFStringEncodingUTF8);
			CFArrayRef paths = CFArrayCreate(kCFAllocatorDefault, reinterpret_cast<const void **>(&cf_path), 1, nullptr);

			FSEventStreamContext context = {0, this, nullptr, nullptr, nullptr};
			m_stream = FSEventStreamCreate(
				kCFAllocatorDefault,
				&bbb_utils_filewatch::fs_callback,
				&context,
				paths,
				kFSEventStreamEventIdSinceNow,
				latency_attr,
				kFSEventStreamCreateFlagFileEvents);

			CFRelease(paths);
			CFRelease(cf_path);

			if(m_stream) {
				FSEventStreamScheduleWithRunLoop(m_stream, m_run_loop, kCFRunLoopDefaultMode);
				FSEventStreamStart(m_stream);
			}

			CFRunLoopRun();

			if(m_stream) {
				FSEventStreamStop(m_stream);
				FSEventStreamInvalidate(m_stream);
				FSEventStreamRelease(m_stream);
				m_stream = nullptr;
			}
		});

		c74::min::atoms status;
		status.push_back(c74::min::symbol("watching"));
		status.push_back(c74::min::symbol(path));
		status_out.send(status);
	}

	void stop_watching() {
		if(m_run_loop) {
			CFRunLoopStop(m_run_loop);
		}
		if(m_thread.joinable()) {
			m_thread.join();
		}
		m_running.store(false);
		status_out.send(c74::min::symbol("stopped"));
	}

	static void fs_callback(
		ConstFSEventStreamRef,
		void *client_callback_info,
		size_t num_events,
		void *event_paths,
		const FSEventStreamEventFlags[],
		const FSEventStreamEventId[]) {
		auto *self = static_cast<bbb_utils_filewatch *>(client_callback_info);
		auto **paths = static_cast<CFStringRef *>(event_paths);

		{
			std::lock_guard<std::mutex> lock(self->m_changes_mutex);
			for(size_t i = 0; i < num_events; ++i) {
				char buffer[PATH_MAX];
				CFStringGetCString(paths[i], buffer, sizeof(buffer), kCFStringEncodingUTF8);
				self->m_pending_changes.push_back(buffer);
			}
		}
		self->m_queue.set();
	}

	void deliver_changes() {
		std::vector<std::string> changes;
		{
			std::lock_guard<std::mutex> lock(m_changes_mutex);
			std::swap(changes, m_pending_changes);
		}
		for(const auto &c : changes) {
			changed_out.send(c74::min::symbol(c));
		}
	}
};

MIN_EXTERNAL(bbb_utils_filewatch);
