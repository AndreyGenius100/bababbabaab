#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"

int wmain(int argc, wchar_t* argv[])
{
    std::locale::global(std::locale(""));

    Log::LOG log = Log::INITLOG;

    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);
        Log::WriteLine(log, "Тест: ", "\n", "");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);

        In::IN in = In::getin(parm.in);
        Log::WriteIn(log, in);

        Log::Close(log);
    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
        Log::Close(log);
        return e.id;
    }

    return 0;
}
