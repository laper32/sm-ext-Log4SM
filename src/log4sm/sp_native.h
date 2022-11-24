#ifndef _LOG4SM_SP_NATIVE_H
#define _LOG4SM_SP_NATIVE_H

#pragma once

#include <log4sm/shared.h>

namespace log4sm {

extern sp_nativeinfo_t g_Log4SMNative[];

namespace api {

namespace logger {

extern cell_t Create(IPluginContext*, const cell_t*);
extern cell_t Remove(IPluginContext*, const cell_t*);
extern cell_t Trace(IPluginContext*, const cell_t*);
extern cell_t Debug(IPluginContext*, const cell_t*);
extern cell_t Info(IPluginContext*, const cell_t*);
extern cell_t Warn(IPluginContext*, const cell_t*);
extern cell_t Error(IPluginContext*, const cell_t*);
extern cell_t Fatal(IPluginContext*, const cell_t*);
extern cell_t SetLevel(IPluginContext*, const cell_t*);
extern cell_t SetPattern(IPluginContext*, const cell_t*);

} // namespace logger

} // namespace api

} // namespace log4sm

#endif // !_LOG4SM_SP_NATIVE_H
