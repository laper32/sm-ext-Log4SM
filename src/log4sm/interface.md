```cpp
#ifndef _SMEXT_LOG4SM_INTERFACE_H
#define _SMEXT_LOG4SM_INTERFACE_H

#pragma once

#include <IShareSys.h>

#define SMINTERFACE_LOG4SM_NAME "ILog4SM"
#define SMINTERFACE_LOG4SM_VERSION 1

class ILogger
{
public:
	virtual ~ILogger() { }
	virtual const char* Name() = 0;
	virtual void Trace(const char* fmt) = 0;
	virtual void Debug(const char* fmt) = 0;
	virtual void Info(const char* fmt) = 0;
	virtual void Warn(const char* fmt) = 0;
	virtual void Error(const char* fmt) = 0;
	virtual void Fatal(const char* fmt) = 0;
	virtual void SetLevel(int lvl) = 0;
	virtual void SetPattern(const char* fmt) = 0;
};

class ILogManager
{
public:
	virtual ILogger* CreateLogger(bool to_game_console, const char* name) = 0;
};

class ILog4SM : public SMInterface
{
public:
	virtual const char* GetInterfaceName()
	{
		return SMINTERFACE_LOG4SM_NAME;
	}
	virtual unsigned int GetInterfaceVersion()
	{
		return SMINTERFACE_LOG4SM_VERSION;
	}
	virtual ILogManager* GetManager() = 0;
};

#endif // !_SMEXT_LOG4SM_INTERFACE_H

```