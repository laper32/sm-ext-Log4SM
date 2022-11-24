#include <log4sm/sp_native.h>

#include <log4sm/sm_handler.h>
#include <log4sm/sm_interface.h>

#include <extsdk/interop.hpp>

sp_nativeinfo_t log4sm::g_Log4SMNative[] = {
    { "Logger.Logger", api::logger::Create },
    { "Logger.Remove", api::logger::Remove },
    { "Logger.Trace", api::logger::Trace },
    { "Logger.Debug", api::logger::Debug },
    { "Logger.Info", api::logger::Info },
    { "Logger.Warn", api::logger::Warn },
    { "Logger.Error", api::logger::Error },
    { "Logger.Fatal", api::logger::Fatal },
    { "Logger.SetPattern", api::logger::SetPattern },
    { nullptr, nullptr }
};

cell_t log4sm::api::logger::Create(IPluginContext* pContext, const cell_t* params)
{
    bool to_game_console = false;
    extsdk::interop::cell2native(pContext, params[1], to_game_console);

    std::string name;
    extsdk::interop::cell2native(pContext, params[2], name);
    if (spdlog::get(name))
    {
        pContext->ReportError("Instance already exists: %s", name.c_str());
        return BAD_HANDLE;
    }

    ILogger* logger = g_LogManager->CreateLogger(to_game_console, name.c_str());
    HandleError ec = {};
    Handle_t hndl = handlesys->CreateHandle(hndl::hLogger, logger, pContext->GetIdentity(), myself->GetIdentity(), &ec);
    if (ec != HandleError_None)
    {
        pContext->ReportError("Error occured when creating handle. Error code: %d\n", ec);
        return BAD_HANDLE;
    }

    return hndl;
}

cell_t log4sm::api::logger::Remove(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };
    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("Error occured when reading handle. Error code: %d", ec);
        return -1;
    }

    // Remove is equivalent to free this handle.
    handlesys->FreeHandle(hndl, &sec);

    return 0;
}

cell_t log4sm::api::logger::Trace(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };

    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("%s", fmt::format("Invalid occured when retriving handle. Error code: %d", ec).c_str());
        return -1;
    }
    char buffer[1024] = {};
    {
        DetectExceptions eh(pContext);
        smutils->FormatString(buffer, sizeof(buffer), pContext, params, 2);
        if (eh.HasException())
        {
            return 0;
        }
    }
    raw->Trace(buffer);

    return 0;
}

cell_t log4sm::api::logger::Debug(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };

    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("%s", fmt::format("Invalid occured when retriving handle. Error code: %d", ec).c_str());
        return -1;
    }
    char buffer[1024] = {};
    {
        DetectExceptions eh(pContext);
        smutils->FormatString(buffer, sizeof(buffer), pContext, params, 2);
        if (eh.HasException())
        {
            return 0;
        }
    }
    raw->Debug(buffer);

    return 0;
}

cell_t log4sm::api::logger::Info(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };

    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("%s", fmt::format("Invalid occured when retriving handle. Error code: %d", ec).c_str());
        return -1;
    }
    char buffer[1024] = {};
    {
        DetectExceptions eh(pContext);
        smutils->FormatString(buffer, sizeof(buffer), pContext, params, 2);
        if (eh.HasException())
        {
            return 0;
        }
    }
    raw->Info(buffer);

    return 0;
}

cell_t log4sm::api::logger::Warn(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };

    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("%s", fmt::format("Invalid occured when retriving handle. Error code: %d", ec).c_str());
        return -1;
    }
    char buffer[1024] = {};
    {
        DetectExceptions eh(pContext);
        smutils->FormatString(buffer, sizeof(buffer), pContext, params, 2);
        if (eh.HasException())
        {
            return 0;
        }
    }
    raw->Warn(buffer);

    return 0;
}

cell_t log4sm::api::logger::Error(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };

    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("%s", fmt::format("Invalid occured when retriving handle. Error code: %d", ec).c_str());
        return -1;
    }
    char buffer[1024] = {};
    {
        DetectExceptions eh(pContext);
        smutils->FormatString(buffer, sizeof(buffer), pContext, params, 2);
        if (eh.HasException())
        {
            return 0;
        }
    }
    raw->Error(buffer);

    return 0;
}

cell_t log4sm::api::logger::Fatal(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };

    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("%s", fmt::format("Invalid occured when retriving handle. Error code: %d", ec).c_str());
        return -1;
    }
    char buffer[1024] = {};
    {
        DetectExceptions eh(pContext);
        smutils->FormatString(buffer, sizeof(buffer), pContext, params, 2);
        if (eh.HasException())
        {
            return 0;
        }
    }
    raw->Fatal(buffer);

    return 0;
}

cell_t log4sm::api::logger::SetLevel(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };

    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("%s", fmt::format("Invalid occured when retriving handle. Error code: %d", ec).c_str());
        return -1;
    }

    int lvl = 0;
    extsdk::interop::cell2native(pContext, params[2], lvl);
    raw->SetLevel(lvl);

    return 0;
}

cell_t log4sm::api::logger::SetPattern(IPluginContext* pContext, const cell_t* params)
{
    Handle_t hndl = static_cast<Handle_t>(params[1]);
    HandleError ec = {};
    HandleSecurity sec = { nullptr, myself->GetIdentity() };

    ILogger* raw = nullptr;
    if (ec = handlesys->ReadHandle(hndl, hndl::hLogger, &sec, (void**)&raw); ec != HandleError_None)
    {
        pContext->ReportError("%s", fmt::format("Invalid occured when retriving handle. Error code: %d", ec).c_str());
        return -1;
    }
    std::string pattern;
    extsdk::interop::cell2native(pContext, params[2], pattern);
    raw->SetPattern(pattern.c_str());

    return 0;
}
