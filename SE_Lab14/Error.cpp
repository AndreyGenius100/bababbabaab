#include "stdafx.h"
#include "Error.h"

namespace Error {

    // ������� ��������� (��� 0�ERROR_MAX_ENTRY-1)
    static ERROR errors[ERROR_MAX_ENTRY] = {
        ERROR_ENTRY(0,   "������������ ��� ������"),
        ERROR_ENTRY(1,   "��������� ����"),
        // 2�9 � undefined
        ERROR_ENTRY_NODEF10(2),
        // 10�99 � undefined
        ERROR_ENTRY_NODEF10(10),
        // 100�109 � ������ ����������
        ERROR_ENTRY(100, "�������� -in ������ ���� �����"),
        ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
        ERROR_ENTRY(104, "��������� ����� �������� ���������"),
        ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
        ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
        // 110�119 � ������ ������
        ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
        ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in)"),
        ERROR_ENTRY(112, "������ ��� �������� ����� ���������(-log)"),
        ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
        ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
        // ��������� � undefined
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
