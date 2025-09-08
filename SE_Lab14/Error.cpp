#include "stdafx.h"
#include "Error.h"

namespace Error {

    // “аблица сообщений (код 0ЕERROR_MAX_ENTRY-1)
    static ERROR errors[ERROR_MAX_ENTRY] = {
        ERROR_ENTRY(0,   "Ќедопустимый код ошибки"),
        ERROR_ENTRY(1,   "—истемный сбой"),
        // 2Е9 Ц undefined
        ERROR_ENTRY_NODEF10(2),
        // 10Е99 Ц undefined
        ERROR_ENTRY_NODEF10(10),
        // 100Е109 Ц ошибки параметров
        ERROR_ENTRY(100, "ѕараметр -in должен быть задан"),
        ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
        ERROR_ENTRY(104, "ѕревышена длина входного параметра"),
        ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
        ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
        // 110Е119 Ц ошибки файлов
        ERROR_ENTRY(110, "ќшибка при открытии файла с исходным кодом (-in)"),
        ERROR_ENTRY(111, "Ќедопустимый символ в исходном файле (-in)"),
        ERROR_ENTRY(112, "ќшибка при создании файла протокола(-log)"),
        ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
        ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
        // остальные Ц undefined
        ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),
        ERROR_ENTRY_NODEF100(500), ERROR_ENTRY_NODEF100(600), ERROR_ENTRY_NODEF100(700),
        ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
    };

    ERROR geterror(int id) {
        if (id <= 0 || id >= ERROR_MAX_ENTRY) id = 0;
        return errors[id];
    }

    ERROR geterrorin(int id, int line, int col) {
        if (id <= 0 || id >= ERROR_MAX_ENTRY) id = 0;
        ERROR e = errors[id];
        e.inext.line = (short)line;
        e.inext.col = (short)col;
        return e;
    }

}
