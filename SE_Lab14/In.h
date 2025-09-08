#pragma once

#include <fstream>
#include <string>
#include <cstring>
#include "Error.h"

// макросы, соответствующие вашему ТЗ из Windows-1251
// тут мы даём упрощённый пример: разрешаем печатные ASCII (32–126) и '\n',
// игнорируем '\r', всё остальное — запрещено.
// при необходимости замените table[] на вашу полную IN_CODE_TABLE.
#define IN_MAX_LEN_TEXT (1024*1024)
#define IN_CODE_ENDL    '\n'

namespace In {

    struct IN {
        enum { T = 1024, F = 2048, I = 4096 };
        int    size;           // число записанных символов
        int    lines;          // число строк
        int    ignor;          // число пропущенных символов
        char* text;           // буфер текста (Windows-1251)
        int    code[256];      // таблица правил
    };

    // Вводим файл, проверяем символы, заполняем IN или бросаем ERROR_THROW_IN(111,…)
    IN getin(const wchar_t infile[]);

}
