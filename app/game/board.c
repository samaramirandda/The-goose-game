int getBoardSize()
{
    int boardSize = BOARD_0;
    char boardType[2];

    do
    {
        Screen.clear();
        Screen.title("\tESCOLHA DO TABULEIRO");

        if (error)
            Exceptions.printError();

        printf(COLOR_Blue "\n\n> Qual o tamanho do tabuleiro? (S - Pequeno | M - Medio | L - Grande)\n- " COLOR_Default);
        scanf("%s", boardType);

        if (!strstr(boardType, "S") &&
            !strstr(boardType, "M") &&
            !strstr(boardType, "L"))
        {
            Exceptions.setError("Esse tamanho de tabuleiro não existe! Por favor, selecione dentro dos disponíveis!");
        }
    } while (error);

    if (strcmp(boardType, "S") == 0)
        boardSize = BOARD_S;
    else if (strcmp(boardType, "M") == 0)
        boardSize = BOARD_M;
    else if (strcmp(boardType, "L") == 0)
        boardSize = BOARD_L;

    return boardSize;
}

void generateGameBoard(char gameBoard[], int size)
{
    memset(gameBoard, ' ', size);
}

void printGameBoard(char gameBoard[], int *playerPositions, int playerAmount, int size)
{
    for (int i = 0; i < size; i++)
    {
        char playerCharacters[4] = {' ', ' ', ' ', ' '};

        printf(" ");

        putchar(GAMECH_VERTICAL);

        bool playersPresent = false;

        for (int j = 0; j < playerAmount; j++)
        {
            if (playerPositions[j] == i)
            {
                playerCharacters[j] = '1' + j;
                playersPresent = true;
            }
        }

        if (playersPresent)
        {
            printf("%-1c%-1c%-1c%-1c", playerCharacters[0], playerCharacters[1], playerCharacters[2], playerCharacters[3]);
        }
        else
        {
            printf("%-4s", "");
        }

        if (i % BOARD_WIDTH == BOARD_WIDTH - 1)
        {
            putchar(GAMECH_VERTICAL);
            putchar('\n');
        }
    }
}