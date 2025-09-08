#include "stdafx.h"
#include "In.h"
#include <locale>
#include <cwchar>
#include <cstdlib>

namespace In {

    using namespace Error;

    // утилита: wchar_t* → std::string (multi-byte)
    static std::string toMb(const wchar_t* w) {
        size_t len = wcstombs(nullptr, w, 0);
        std::string s(len, '\0');
        wcstombs(&s[0], w, len + 1);
        return s;
    }

    IN getin(const wchar_t infile[]) {
        IN in{};
        in.lines = 0;
        in.size = 0;
        in.ignor = 0;
        in.text = new char[IN_MAX_LEN_TEXT + 1];

        // инициализируем таблицу правил
        for (int i = 0; i < 256; ++i) {
            if (i == '\r')          in.code[i] = IN::I;
            else if (i == IN_CODE_ENDL)  in.code[i] = IN::T;
            else if (i >= 32 && i <= 126) in.code[i] = IN::T;
            else                         in.code[i] = IN::F;
        }

        // открываем входной файл в бинарном режиме
        std::string path = toMb(infile);
        std::ifstream f(path, std::ios::binary);
        if (!f.is_open())
            throw ERROR_THROW(110);

        unsigned char ch;
        int col = 0;
        while (f.read((char*)&ch, 1)) {
            int rule = in.code[ch];

            if (rule == IN::F) {
                // запрещённый символ → кидаем с указанием строки/столбца
                throw ERROR_THROW_IN(111, in.lines, col);
            }
            else if (rule == IN::I) {
                // игнорируем (увеличиваем счётчик пропущенных)
                ++in.ignor;
            }
            else {
                // разрешён → записываем
                in.text[in.size++] = char(ch);
            }

            // учитываем перевод строки
            if (ch == IN_CODE_ENDL) {
                ++in.lines;
                col = 0;
            }
            else {
                ++col;
            }
        }
        // нуль-терминируем буфер
        in.text[in.size] = '\0';
        return in;
    }

}
