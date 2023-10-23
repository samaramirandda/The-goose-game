void startCursor()
{
    printf("\e[0G");
}

void homeCursor()
{
    printf("\e[H");
}

void moverCursor(int line, int column)
{
    printf("\e[%d;%dH", line, column);
}

void upCursor(int lines)
{
    printf("\e[%dA", lines);
}

void downCursor(int lines)
{
    printf("\e[%dB", lines);
}

void rightCursor(int columns)
{
    printf("\e[%dC", columns);
}

void leftCursor(int columns)
{
    printf("\e[%dD", columns);
}

void saveCursor()
{
    printf("\e[s");
}

void restoreCursor()
{
    printf("\e[u");
}