typedef struct cursor {
    void (*startCursor)();
    void (*homeCursor)();
    void (*moverCursor)(int linha, int coluna);
    void (*upCursor)(int linhas);
    void (*downCursor)(int linhas);
    void (*rightCursor)(int colunas);
    void (*leftCursor)(int colunas);
    void (*saveCursor)();
    void (*restoreCursor)();
} CursorController;

#include "cursor.c"