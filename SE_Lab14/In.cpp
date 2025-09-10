#include "stdafx.h"
#include "In.h"
#include "Error.h"

namespace In
{
    static int table[256] = IN_CODE_TABLE;

    IN getin(const wchar_t infile[])
    {
        IN result = { 0, 0, 0, nullptr, {0} };
        std::ifstream file(infile, std::ios::binary);
        if (!file.is_open())
            throw ERROR_THROW(110);

        // копируем проверочную таблицу
        for (int i = 0; i < 256; ++i)
            result.code[i] = table[i];

        result.text = new unsigned char[IN_MAX_LEN_TEXT];
        int idx = 0, col = 0;
        char ch = 0;

        while (file.get(ch))
        {
            unsigned char uch = static_cast<unsigned char>(ch);
            int rule = result.code[uch];

            if (rule == IN::F)
                throw ERROR_THROW_IN(111, result.lines, col);

            if (rule >= 0 && rule < 256)
            {
                result.text[idx++] = static_cast<unsigned char>(rule);
            }
            else if (rule == IN::T)
            {
                result.text[idx++] = uch;
            }
            else if (rule == IN::I)
            {
                ++result.ignor;
                // пропустить
            }

            ++col;
            if (ch == IN_CODE_ENDL)
            {
                ++result.lines;
                col = 0;
            }
        }

        result.size = idx;
        result.text[idx] = 0; // нуль-терминатор
        return result;
    }
}
