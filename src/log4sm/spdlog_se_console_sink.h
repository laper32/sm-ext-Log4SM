#ifndef _LOG4SM_SPDLOG_SE_CONSOLE_SINK_H
#define _LOG4SM_SPDLOG_SE_CONSOLE_SINK_H

#pragma once

#include <log4sm/shared.h>
#include <extsdk/ent_cast.hpp>

namespace spdlog::sinks {

template<typename Mutex>
class source_engine_console_sink : public base_sink<Mutex>
{
protected:
	void sink_it_(const spdlog::details::log_msg& msg) override
	{
		memory_buf_t formatted;
		base_sink<Mutex>::formatter_->format(msg, formatted);
		std::string result = fmt::to_string(formatted);

		auto PrintToConsole = [&](int id, const char* msg) {
			if (id > 0) {
				IGamePlayer* player = extsdk::ent_cast<IGamePlayer*>(id);
				if (!player) return;
				if (!player->IsInGame()) return;
				if (player->IsFakeClient()) return;
				player->PrintToConsole(msg);
			}
		};

		auto PrintToConsoleAll = [&](const char* msg) {
			for (int i = 1; i < playerhelpers->GetMaxClients(); i++) {
				PrintToConsole(i, msg);
			}
		};
		PrintToConsoleAll(result.c_str());
	}

	void flush_() override
	{
	}
};

using source_engine_console_sink_mt = source_engine_console_sink<std::mutex>;
using source_engine_console_sink_nt = source_engine_console_sink<details::null_mutex>;


} // namespace spdlog::sinks

#endif // !_LOG4SM_SPDLOG_SE_CONSOLE_SINK_H
