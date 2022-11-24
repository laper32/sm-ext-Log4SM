#ifndef _LOG4SM_SPDLOG_NON_LOCK_FILE_SINK_H
#define _LOG4SM_SPDLOG_NON_LOCK_FILE_SINK_H

namespace spdlog::sinks {

template<typename Mutex>
class non_lock_file_sink : public base_sink<Mutex>
{
public:
	explicit non_lock_file_sink(const filename_t& filename, bool truncate = false) : _filename(filename), _truncate(truncate)
	{
	}

	~non_lock_file_sink()
	{
		flush_();
	}

	const filename_t& filename() const
	{
		return _filename;
	}
protected:
	void sink_it_(const details::log_msg& msg) override {
		memory_buf_t formatted;
		base_sink<Mutex>::formatter_->format(msg, formatted);
		line_drive.emplace_back(std::move(formatted));
		/*std::unique_ptr<fmt::memory_buffer> formatted(new fmt::memory_buffer);
		sink::formatter_->format(msg, *formatted);
		line_drive.push_back(std::move(formatted));*/
	}

	void flush_() override {
		if (!line_drive.empty()) {
			try {
				file_helper_.open(_filename, _truncate);
			}
			catch (...) {}
			for (auto& self : line_drive) {
				try {
					file_helper_.write(self);
				} catch(...) {}
			}
			//for (std::unique_ptr<fmt::memory_buffer>& pbuf : line_drive) {
			//	try {
			//		file_helper_.write(*pbuf);
			//		//std::get(pbuf);
			//		//file_helper_.write(*pbuf.get());
			//	}
			//	catch (...) {}
			//}
			line_drive.clear();
			file_helper_.flush();
			file_helper_.close();
		}
	}
private:
	details::file_helper file_helper_;
	filename_t _filename;
	bool _truncate;
	std::list<memory_buf_t> line_drive;
	//std::list<std::unique_ptr<fmt::memory_buffer>> line_drive;
};
using non_lock_file_sink_mt = non_lock_file_sink<std::mutex>;
using non_lock_file_sink_st = non_lock_file_sink<details::null_mutex>;
} // namespace spdlog::sinks

#endif // !_LOG4SM_SPDLOG_NON_LOCK_FILE_SINK_H
