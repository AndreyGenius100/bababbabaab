#include "stdafx.h"
#include "Parm.h"
#include "Error.h"
#include <cwchar>

namespace Parm
{
    PARM getparm(int argc, wchar_t* argv[])
    {
        PARM p = { L"", L"", L"" };
        // Найти -in:
        for (int i = 1; i < argc; ++i)
        {
            if (wcsncmp(argv[i], PARM_IN, wcslen(PARM_IN)) == 0)
                wcscpy_s(p.in, argv[i] + wcslen(PARM_IN));
            else if (wcsncmp(argv[i], PARM_OUT, wcslen(PARM_OUT)) == 0)
                wcscpy_s(p.out, argv[i] + wcslen(PARM_OUT));
            else if (wcsncmp(argv[i], PARM_LOG, wcslen(PARM_LOG)) == 0)
                wcscpy_s(p.log, argv[i] + wcslen(PARM_LOG));
        }

        if (wcslen(p.in) == 0)
            throw ERROR_THROW(100);

        // по умолчанию для out/log
        if (wcslen(p.out) == 0)
        {
            wcscpy_s(p.out, p.in);
            wcsncat_s(p.out, PARM_OUT_DEFAULT_EXT, PARM_MAX_SIZE - 1);
        }
        if (wcslen(p.log) == 0)
        {
            wcscpy_s(p.log, p.in);
            wcsncat_s(p.log, PARM_LOG_DEFAULT_EXT, PARM_MAX_SIZE - 1);
        }

        // Проверка длины
        if (wcslen(p.in) >= PARM_MAX_SIZE ||
            wcslen(p.out) >= PARM_MAX_SIZE ||
            wcslen(p.log) >= PARM_MAX_SIZE)
            throw ERROR_THROW(104);

        return p;
    }
}
