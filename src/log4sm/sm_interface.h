#ifndef _LOG4SM_SM_INTERFACE_H
#define _LOG4SM_SM_INTERFACE_H

#pragma once

#include <log4sm/shared.h>

namespace log4sm {

class Logger : public ILogger
{
public:
	Logger(bool to_game_console, const char* name);
	~Logger();
	const char* Name();
	void Trace(const char* fmt);
	void Debug(const char* fmt);
	void Info(const char* fmt);
	void Warn(const char* fmt);
	void Error(const char* fmt);
	void Fatal(const char* fmt);
	void SetLevel(int lvl);
	void SetPattern(const char* fmt);

private:
	std::shared_ptr<spdlog::async_logger> _impl;
};

class LogManager : public ILogManager
{
public:
	LogManager();
	~LogManager();
	ILogger* CreateLogger(bool to_game_console, const char* name);
};

class Log4SM : public ILog4SM
{
public:
	ILogManager* GetManager();
};

extern std::unique_ptr<LogManager> g_LogManager;
extern Log4SM g_Log4SM;

} // namespace log4sm

#endif // !_LOG4SM_SM_INTERFACE_H
