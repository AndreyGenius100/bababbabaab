
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Log.h"
#include <ctime>



namespace Log
{
    static void convert_wchar(const wchar_t* w, char* buf, size_t sz)
    {
        std::wcstombs(buf, w, sz);
        buf[sz - 1] = '\0';
    }

    LOG getlog(const wchar_t logfile[])
    {
        LOG lg = { L"", nullptr };
        wcscpy_s(lg.logfile, logfile);
        lg.stream = new std::ofstream;
        char path[PARM_MAX_SIZE];
        convert_wchar(logfile, path, PARM_MAX_SIZE);
        lg.stream->open(path, std::ios::out | std::ios::trunc);
        if (!lg.stream->is_open())
            throw Error::geterror(112);
        return lg;
    }

    void WriteLine(LOG log, const char* c, ...)
    {
        if (!log.stream) return;
        va_list args; va_start(args, c);
        while (c && *c)
        {
            *log.stream << c;
            c = va_arg(args, const char*);
        }
        va_end(args);
    }

    void WriteLine(LOG log, const wchar_t* c, ...)
    {
        if (!log.stream) return;
        va_list args; va_start(args, c);
        char buf[1024];
        while (c && *c)
        {
            convert_wchar(c, buf, sizeof(buf));
            *log.stream << buf;
            c = va_arg(args, const wchar_t*);
        }
        va_end(args);
    }

    void WriteLog(LOG log)
    {
        if (!log.stream) return;
        time_t t; time(&t);
        struct tm tm; localtime_s(&tm, &t);
        char timestr[64];
        strftime(timestr, sizeof(timestr), "Протокол %d.%m.%Y %H:%M:%S\n", &tm);
        *log.stream << timestr;
    }

    void WriteParm(LOG log, Parm::PARM parm)
    {
        WriteLine(log, "Параметры\n", "");
        WriteLine(log, "-in: ", (char*)nullptr, "");
        char buf[PARM_MAX_SIZE];
        convert_wchar(parm.in, buf, PARM_MAX_SIZE);
        *log.stream << buf << "\n";
        WriteLine(log, "-out: ", "");
        convert_wchar(parm.out, buf, PARM_MAX_SIZE);
        *log.stream << buf << "\n";
        WriteLine(log, "-log: ", "");
        convert_wchar(parm.log, buf, PARM_MAX_SIZE);
        *log.stream << buf << "\n";
    }

    void WriteIn(LOG log, In::IN in)
    {
        WriteLine(log, "Исходные данные\n", "");
        *log.stream << "Количество символов: " << in.size << "\n";
        *log.stream << "Проигнорировано: " << in.ignor << "\n";
        *log.stream << "Количество строк: " << in.lines << "\n";
    }

    void WriteError(LOG log, Error::ERROR err)
    {
        char buf[256];
        std::snprintf(buf, sizeof(buf), "Ошибка %d: %s", err.id, err.message);
        if (log.stream)
        {
            *log.stream << buf;
            if (err.inext.line >= 0)
                *log.stream << ", строка " << err.inext.line
                << ", позиция " << err.inext.col;
        }
        else
        {
            std::cout << buf;
            if (err.inext.line >= 0)
                std::cout << ", строка " << err.inext.line
                << ", позиция " << err.inext.col;
            std::cout << std::endl;
        }
    }

    void Close(LOG log)
    {
        if (log.stream)
        {
            log.stream->close();
            delete log.stream;
        }
    }
}
