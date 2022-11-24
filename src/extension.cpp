#include <detail/ext.h>
#include <log4sm/main.h>

#include <extsdk/ent_cast.hpp>

Extension g_Ext;

SMEXT_LINK(&g_Ext);

bool Extension::SDK_OnLoad(char* error, size_t maxlen, bool late)
{
	
	if (!detail::SDK_OnLoad(error, maxlen, late))
	{
		return false;
	}

	if (!log4sm::SDK_OnLoad(error, maxlen, late))
	{
		return false;
	}
	return SDKExtension::SDK_OnLoad(error, maxlen, late);
}

void Extension::SDK_OnUnload()
{
	log4sm::SDK_OnUnload();
	detail::SDK_OnUnload();

	return SDKExtension::SDK_OnUnload();
}

void Extension::SDK_OnAllLoaded()
{
	detail::SDK_OnAllLoaded();
	log4sm::SDK_OnAllLoaded();

	return SDKExtension::SDK_OnAllLoaded();
}

bool Extension::SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	if (!detail::SDK_OnMetamodLoad(ismm, error, maxlen, late))
	{
		return false;
	}

	if (!log4sm::SDK_OnMetamodLoad(ismm, error, maxlen, late))
	{
		return false;
	}

	return SDKExtension::SDK_OnMetamodLoad(ismm, error, maxlen, late);
}
