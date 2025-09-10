#pragma once

#include "In.h"
#include "Parm.h"
#include "Error.h"
#include <fstream>

namespace Log
{
    struct LOG
    {
        wchar_t logfile[PARM_MAX_SIZE];
        std::ofstream* stream;
    };
    static const LOG INITLOG{ L"", nullptr };

    LOG getlog(const wchar_t logfile[]);
    void WriteLine(LOG log, const char* c, ...);
    void WriteLine(LOG log, const wchar_t* c, ...);
    void WriteLog(LOG log);
    void WriteParm(LOG log, Parm::PARM parm);
    void WriteIn(LOG log, In::IN in);
    void WriteError(LOG log, Error::ERROR err);
    void Close(LOG log);
}
