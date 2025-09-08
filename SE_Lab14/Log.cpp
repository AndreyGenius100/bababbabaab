#include "stdafx.h"
#include "Log.h"

namespace Log {

    using namespace Error;

    static std::string toMb(const wchar_t* w) {
        size_t len = wcstombs(nullptr, w, 0);
        std::string s(len, '\0');
        wcstombs(&s[0], w, len + 1);
        return s;
    }

    LOG getlog(const wchar_t logfile[]) {
        LOG lg;
        wcscpy_s(lg.logfile, logfile);
        lg.stream = new std::ofstream;
        std::string path = toMb(logfile);
        lg.stream->open(path);
        if (!lg.stream->is_open()) throw ERROR_THROW(112);
        return lg;
    }

    void WriteLine(LOG log, const char* c, ...) {
        va_list args;
        va_start(args, c);
        while (c && *c) {
            *log.stream << c;
            c = va_arg(args, const char*);
        }
        va_end(args);
    }

    void WriteLine(LOG log, const wchar_t* c, ...) {
        va_list args;
        va_start(args, c);
        while (c && *c) {
            std::string mb = toMb(c);
            *log.stream << mb;
            c = va_arg(args, const wchar_t*);
        }
        va_end(args);
    }

    void WriteLog(LOG log) {
        char buf[64];
        time_t t = time(nullptr);
        tm now;
        localtime_s(&now, &t);
        strftime(buf, sizeof buf, "Протокол %d.%m.%Y %H:%M:%S\n", &now);
        WriteLine(log, buf, "");
    }

    void WriteParm(LOG log, const Parm::PARM& p) {
        WriteLine(log,
            (wchar_t*)L"Параметры\n",
            (wchar_t*)L"-log: ", p.log, L"\n",
            (wchar_t*)L"-out: ", p.out, L"\n",
            (wchar_t*)L"-in: ", p.in, L"\n", L"");
    }

    void WriteIn(LOG log, const In::IN& in) {
        WriteLine(log, (char*)"Исходные данные\n", "");
        WriteLine(log, (char*)"Количество символов: ", nullptr);
        *log.stream << in.size << "\n";
        WriteLine(log, (char*)"Проигнорировано: ", nullptr);
        *log.stream << in.ignor << "\n";
        WriteLine(log, (char*)"Количество строк: ", nullptr);
        *log.stream << in.lines << "\n";
    }

    void WriteError(LOG log, const Error::ERROR& e) {
        char buf[256];
        sprintf_s(buf, "Ошибка %d: %s", e.id, e.message);
        if (log.stream) {
            *log.stream << buf;
            if (e.inext.line >= 0)
                *log.stream << ", строка " << e.inext.line << ", позиция " << e.inext.col;
            *log.stream << "\n";
        }
        else {
            std::cout << buf;
            if (e.inext.line >= 0)
                std::cout << ", строка " << e.inext.line << ", позиция " << e.inext.col;
            std::cout << std::endl;
        }
    }

    void Close(LOG log) {
        if (log.stream) {
            log.stream->close();
            delete log.stream;
        }
    }

}
