#ifndef _LOG4SM_SM_HANDLER_H
#define _LOG4SM_SM_HANDLER_H

#pragma once

#include <log4sm/shared.h>

namespace log4sm {

class LoggerHandler : public IHandleTypeDispatch
{
public:
	void OnHandleDestroy(HandleType_t type, void* object);
};

namespace hndl {

extern HandleType_t hLogger;
extern LoggerHandler sLoggerHandler;

} // namespace hndl

} // namespace log4sm

#endif // !_LOG4SM_SM_HANDLER_H
