#include <log4sm/main.h>
#include <log4sm/sm_handler.h>
#include <log4sm/sm_interface.h>
#include <log4sm/sp_native.h>

namespace log4sm {

Log4SM g_Log4SM;
std::unique_ptr<LogManager> g_LogManager = nullptr;

} // namespace log4sm

bool log4sm::SDK_OnLoad(char* error, size_t maxlen, bool late)
{
	sharesys->AddNatives(myself, g_Log4SMNative);
	sharesys->AddInterface(myself, &g_Log4SM);

	g_LogManager = std::make_unique<LogManager>();

	HandleAccess sec;
	handlesys->InitAccessDefaults(nullptr, &sec);
	sec.access[HandleAccess_Delete] = 0;

	hndl::hLogger = handlesys->CreateType("Logger", &hndl::sLoggerHandler, 0, nullptr, &sec, myself->GetIdentity(), nullptr);

	return true;
}

void log4sm::SDK_OnUnload()
{
	handlesys->RemoveType(hndl::hLogger, myself->GetIdentity());
	
	g_LogManager.reset();
}

void log4sm::SDK_OnAllLoaded()
{

}

bool log4sm::SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	return true;
}
