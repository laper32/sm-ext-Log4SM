#include <log4sm/sm_handler.h>

namespace log4sm::hndl {

HandleType_t hLogger = 0;
LoggerHandler sLoggerHandler;

} // namespace log4sm::hndl

void log4sm::LoggerHandler::OnHandleDestroy(HandleType_t type, void* object)
{
	delete (ILogger*)(object);
}
