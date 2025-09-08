#include "stdafx.h"
#include "Parm.h"
#include "Error.h"

namespace Parm {

    using namespace Error;

    PARM getparm(int argc, wchar_t* argv[]) {
        PARM p = { L"", L"", L"" };

        for (int i = 1; i < argc; ++i) {
            if (wcsncmp(argv[i], PARM_IN, 4) == 0) {
                wchar_t* val = argv[i] + 4;
                if (wcslen(val) >= PARM_MAX_SIZE)
                    throw ERROR_THROW(104);
                wcscpy_s(p.in, val);
            }
            else if (wcsncmp(argv[i], PARM_OUT, 5) == 0) {
                wchar_t* val = argv[i] + 5;
                if (wcslen(val) >= PARM_MAX_SIZE)
                    throw ERROR_THROW(104);
                wcscpy_s(p.out, val);
            }
            else if (wcsncmp(argv[i], PARM_LOG, 5) == 0) {
                wchar_t* val = argv[i] + 5;
                if (wcslen(val) >= PARM_MAX_SIZE)
                    throw ERROR_THROW(104);
                wcscpy_s(p.log, val);
            }
        }

        // обязательный параметр -in
        if (p.in[0] == L'\0')
            throw ERROR_THROW(100);

        // дефолт для -out
        if (p.out[0] == L'\0') {
            wcscpy_s(p.out, p.in);
            wcscat_s(p.out, PARM_OUT_DEFAULT_EXT);
        }

        // дефолт для -log
        if (p.log[0] == L'\0') {
            wcscpy_s(p.log, p.in);
            wcscat_s(p.log, PARM_LOG_DEFAULT_EXT);
        }

        return p;
    }

}
