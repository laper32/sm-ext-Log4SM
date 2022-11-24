#include <detail/ext.h>

bool detail::SDK_OnLoad(char* error, size_t maxlen, bool late)
{
	sharesys->RegisterLibrary(myself, "Log4SM");

	return true;
}

void detail::SDK_OnUnload()
{

}

void detail::SDK_OnAllLoaded()
{

}

bool detail::SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	return true;
}
