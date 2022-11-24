#ifndef _COMMON_SHARED_H
#define _COMMON_SHARED_H

#pragma once

//#include <fmt/std.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <fmt/format.h>

#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif // !SPDLOG_FMT_EXTERNAL

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#define SPDLOG_LEVEL_NAMES { "Trace", "Debug", "Info", "Warn", "Error", "Fatal", "Off" }
#define SPDLOG_SHORT_LEVEL_NAMES { "T", "D", "I", "W", "E", "F", "O" }

#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/dist_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <boost/algorithm/string.hpp>

#endif // !_COMMON_SHARED_H
