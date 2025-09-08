#include "stdafx.h"

using namespace Error;
using namespace Parm;
using namespace Log;
using namespace In;

int wmain(int argc, wchar_t* argv[]) {
    setlocale(LC_ALL, "rus");
    LOG log = INITLOG;
    try {
        PARM parm = getparm(argc, argv);
        log = getlog(parm.log);

        WriteLine(log, (char*)"Тест: ", (char*)"без ошибок\n", "");
        WriteLine(log, (wchar_t*)L"Тест: ", (wchar_t*)L"без ошибок\n", L"");

        WriteLog(log);
        WriteParm(log, parm);

        IN in = getin(parm.in);
        WriteIn(log, in);

        Close(log);
    }
    catch (ERROR& e) {
        WriteError(log, e);
        Close(log);
        return 1;
    }
    return 0;
}
