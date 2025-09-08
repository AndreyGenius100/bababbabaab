#pragma once

// 1. Максимальная длина сообщения
#define ERROR_MAXSIZE_MESSAGE 200

// 2. Размер таблицы ошибок
#define ERROR_MAX_ENTRY 1000

// 3. Базовые макросы для заполнения таблицы
#define ERROR_ENTRY(id, m)            { id, m, { -1, -1 } }
#define ERROR_ENTRY_NODEF(id)         ERROR_ENTRY(id, "Неопределённая ошибка")
#define ERROR_ENTRY_NODEF10(id)       \
    ERROR_ENTRY_NODEF(id+0),  ERROR_ENTRY_NODEF(id+1),  ERROR_ENTRY_NODEF(id+2),  ERROR_ENTRY_NODEF(id+3), \
    ERROR_ENTRY_NODEF(id+4),  ERROR_ENTRY_NODEF(id+5),  ERROR_ENTRY_NODEF(id+6),  ERROR_ENTRY_NODEF(id+7), \
    ERROR_ENTRY_NODEF(id+8),  ERROR_ENTRY_NODEF(id+9)
#define ERROR_ENTRY_NODEF100(id)      \
    ERROR_ENTRY_NODEF10(id+0),  ERROR_ENTRY_NODEF10(id+10),  ERROR_ENTRY_NODEF10(id+20),  ERROR_ENTRY_NODEF10(id+30), \
    ERROR_ENTRY_NODEF10(id+40), ERROR_ENTRY_NODEF10(id+50),  ERROR_ENTRY_NODEF10(id+60),  ERROR_ENTRY_NODEF10(id+70), \
    ERROR_ENTRY_NODEF10(id+80), ERROR_ENTRY_NODEF10(id+90)

// 4. Макросы для генерации исключения
//    ERROR_THROW_IN(id, line, col) — бросает исключение с номером строки и позицией.
#define ERROR_THROW(id)               throw Error::geterror(id)
#define ERROR_THROW_IN(id, line, col) throw Error::geterrorin(id, line, col)

// 5. Макрос для удобного получения C-строки из структуры ERROR
#define ERROR_MESSAGE(err)            ((err).message)

namespace Error {

    struct ERROR {
        int   id;                                   // код ошибки
        char  message[ERROR_MAXSIZE_MESSAGE];       // текст
        struct { short line, col; } inext;         // для ошибок ввода
    };

    // Формируем структуру ERROR по коду
    ERROR geterror(int id);

    // То же, но с указанием строки/столбца
    ERROR geterrorin(int id, int line = -1, int col = -1);

}
