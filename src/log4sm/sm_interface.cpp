#include <log4sm/sm_interface.h>
#include <log4sm/spdlog_se_console_sink.h>
#include <log4sm/spdlog_non_lock_file_sink.h>

log4sm::Logger::Logger(bool to_game_console, const char* name)
{
	auto now = std::time(nullptr);
	auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_mt>();
	if (to_game_console)
	{
		dist_sink->add_sink(std::make_shared<spdlog::sinks::source_engine_console_sink_mt>());
	}
	dist_sink->add_sink(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	char log_path[256] = {};
	// Independent with SM itself, since the logging model is completely different (SM itself logging message with directly I/O).
	smutils->BuildPath(
		Path_SM, log_path, sizeof(log_path), "logs" PLATFORM_SEP "%s", fmt::format("lps-L{:%Y%m%d}.log", fmt::localtime(now)).c_str()
	);

	dist_sink->add_sink(std::make_shared<spdlog::sinks::non_lock_file_sink_mt>(log_path));
	//dist_sink->add_sink(std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("L{:%Y%m%d}.log", fmt::localtime(now))));
	_impl = std::make_shared<spdlog::async_logger>(
		name, dist_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::overrun_oldest
		);
	_impl->set_pattern("L [%Y-%m-%d %H:%M:%S] [%n] [%^%l%$] %v");

	_impl->flush_on(spdlog::level::trace);
	
	spdlog::register_logger(_impl);
}

log4sm::Logger::~Logger()
{
	spdlog::drop(Name());
}

const char* log4sm::Logger::Name()
{
	return _impl->name().c_str();
}

void log4sm::Logger::Trace(const char* fmt)
{
	_impl->trace(fmt);
}

void log4sm::Logger::Debug(const char* fmt)
{
	_impl->debug(fmt);
}

void log4sm::Logger::Info(const char* fmt)
{
	_impl->info(fmt);
}

void log4sm::Logger::Warn(const char* fmt)
{
	_impl->warn(fmt);
}

void log4sm::Logger::Error(const char* fmt)
{
	_impl->error(fmt);
}

void log4sm::Logger::Fatal(const char* fmt)
{
	_impl->critical(fmt);
}

void log4sm::Logger::SetLevel(int lvl)
{
	_impl->set_level(spdlog::level::level_enum(lvl));
}

void log4sm::Logger::SetPattern(const char* fmt)
{
	_impl->set_pattern(fmt);
}

log4sm::LogManager::LogManager()
{
	spdlog::init_thread_pool(8192, 1);
}

log4sm::LogManager::~LogManager()
{
	spdlog::drop_all();
}

ILogger* log4sm::LogManager::CreateLogger(bool to_game_console, const char* name)
{
	return new Logger(to_game_console, name);
}

ILogManager* log4sm::Log4SM::GetManager()
{
	return g_LogManager.get();
}