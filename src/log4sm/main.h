#ifndef _LOG4SM_MAIN_H
#define _LOG4SM_MAIN_H

#pragma once

#include <log4sm/shared.h>

namespace log4sm {

bool SDK_OnLoad(char* error, size_t maxlen, bool late);
void SDK_OnUnload();
void SDK_OnAllLoaded();
bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late);

} // namespace log4sm

#endif // !_LOG4SM_MAIN_H
