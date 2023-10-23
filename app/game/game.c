bool checkVictory(int *playerPositions, int playerAmount, int lastSquare)
{
    for (int i = 0; i < playerAmount; i++)
    {
        if (playerPositions[i] == lastSquare)
        {
            return true;
        }
    }
    return false;
}

void saveGame(GameInfo *game)
{
    FILE *file = fopen("storage/games.bin", "ab");

    while (file == NULL)
    {
        FILE *fileCreate = fopen("storage/games.bin", "w");

        if (fileCreate == NULL)
            return;

        fclose(fileCreate);
    }

    fwrite(game, sizeof(*game), 1, file);

    fclose(file);
}

void end(User *players[4], int *playerPositions, int playerAmount, GameInfo *game)
{
    Screen.clear();

    printf(COLOR_Cyan "\n\
              .-=========-.\n\
              \\'-=======-'/\n\
              _|   .=.   |_\n\
             ((|    1    |))\n\
              \\|   /|\\   |/\n\
               \\__ '`' __/\n\
                 _`) (`_\n\
               _/_______\\_\n\
              /___________\\\\\n\n\n\
\
             " COLOR_Default "Parabéns, " COLOR_Cyan "%s" COLOR_Default "!\n\
      Ganhaste a partida em " COLOR_Green "%d" COLOR_Default " rondas.\n\n\
        Tempo de jogo: " COLOR_Green "%d" COLOR_Default " minutos.\n\n\
\
Respostas " COLOR_Green "certas" COLOR_Default ": " COLOR_Cyan "%d" COLOR_Default "  | Respostas " COLOR_Red "erradas" COLOR_Default ": " COLOR_Cyan "%d" COLOR_Default "\n\n\
Hora de " COLOR_Green "inicio" COLOR_Default ": " COLOR_Cyan "%s" COLOR_Default " | Hora de " COLOR_Red "termino" COLOR_Default ": " COLOR_Cyan "%s" COLOR_Default "\n\n\
\
           " COLOR_Green "Obrigado por jogar :)" COLOR_Default "\n\n\n",
           game->gameWinner.name, game->rounds, game->gameDuration, game->gameWinner.correctAnswers, game->gameWinner.wrongAnswers, game->gameStartTime, game->gameEndTime);

    saveGame(game);

    free(playerPositions);

    for (int i = 0; i < playerAmount; i++)
        Users.logout(players[i]);

    free(game);

    Screen.awaitInteraction();
}

void start(User *players[4], int *playerPositions, int playerAmount, int boardSize)
{
    GameInfo *game = (GameInfo *)malloc(sizeof(GameInfo));
    int correctAnswers[4] = {0, 0, 0, 0};
    int wrongAnswers[4] = {0, 0, 0, 0};
    char *gameBoard = (char *)malloc((boardSize * 2) * sizeof(char));
    char action[100];

    Users.updatePlayingDate(players, playerAmount);
    Board.generateGameBoard(gameBoard, boardSize);

    char currentDate[25];
    int currentHour, currentMinutes;

    int round = 1;

    int startHour, startMinute;
    int endHour, endMinute;

    Functions.getCurrentDate(game->gameDate, sizeof(game->gameDate));
    Functions.getCurrentTime(&startHour, &startMinute);
    sprintf(game->gameStartTime, "%d:%d", startHour, startMinute);

    bool isLastTile[4] = {false, false, false, false},
         gameFinished = false;

    while (!gameFinished)
    {
        for (int i = 0; i < playerAmount; i++)
        {
            fflush(stdin);

            int steps;

            Screen.clear();

            Functions.getCurrentDate(currentDate, sizeof(currentDate));
            Functions.getCurrentTime(&currentHour, &currentMinutes);

            printf(COLOR_Blue "                  THE GOOSE GAME\n");
            printf("                " COLOR_Cyan "%-.2d" COLOR_Blue ":" COLOR_Cyan "%-.2d  %s\n", currentHour, currentMinutes, currentDate);
            printf("\n");
            printf("            " COLOR_Cyan "Ronda:" COLOR_Default " %-2d   " COLOR_Green "|" COLOR_Default "  " COLOR_Cyan "Casa:" COLOR_Default " %d\n", round, Player.getPosition(playerPositions, i));
            printf("            " COLOR_Cyan "Jogador:" COLOR_Default " %-2d " COLOR_Green "|" COLOR_Default "  " COLOR_Cyan "Nome:" COLOR_Default " %s\n", i + 1, players[i]->name);
            printf("\n");
            printf("          --------------------------------\n");
            printf("\n");
            Board.printGameBoard(gameBoard, playerPositions, playerAmount, boardSize);
            printf("\n");
            printf("          --------------------------------\n\n");

            printf(COLOR_Cyan "              PERGUNTA PARA O JOGADOR " COLOR_Green "%d\n\n" COLOR_Default, i + 1);

            if (Questions.askQuestion())
            {
                steps = 1;
                correctAnswers[i]++;

                sprintf(action, "[%d:%d %s] O jogador %s (Numero: %d) acertou uma pergunta e passou para a casa %d.", currentHour, currentMinutes, currentDate, players[i]->name, i, Player.getPosition(playerPositions, i));
                strcpy(game->gameActions[round], action);
            }
            else if (Player.getPosition(playerPositions, i) == 0)
            {
                steps = 0;
                wrongAnswers[i]++;

                sprintf(action, "[%d:%d %s] O jogador %s (Numero: %d) errou uma pergunta e permaneceu na primeira casa.", currentHour, currentMinutes, currentDate, players[i]->name, i);
                strcpy(game->gameActions[round], action);
            }
            else
            {
                steps = -1;
                wrongAnswers[i]++;

                sprintf(action, "[%d:%d %s] O jogador %s (Numero: %d) errou uma pergunta e recuou para a casa %d.", currentHour, currentMinutes, currentDate, players[i]->name, i, Player.getPosition(playerPositions, i));
                strcpy(game->gameActions[round], action);
            }

            if (isLastTile[i] && steps == 1)
            {
                strcpy(game->gameWinner.name, players[i]->name);
                game->gameWinner.correctAnswers = correctAnswers[i];
                game->gameWinner.wrongAnswers = wrongAnswers[i];
                strcpy(game->gameDate, currentDate);

                endHour = currentHour;
                endMinute = currentMinutes;

                sprintf(game->gameEndTime, "%d:%d", endHour, endMinute);

                // Calculate the total minutes for each time
                int totalStartMinutes = startHour * 60 + startMinute;
                int totalEndMinutes = endHour * 60 + endMinute;

                // Calculate the difference in minutes
                int difference = totalEndMinutes - totalStartMinutes;

                // Adjust for crossing midnight if necessary
                if (difference < 0)
                    difference += 24 * 60;

                game->gameDuration = difference;

                sprintf(action, "[%d:%d %s] O jogador %s (Numero: %d) terminou o jogo!", currentHour, currentMinutes, currentDate, players[i]->name, i);
                strcpy(game->gameActions[round], action);

                gameFinished = true;
            }

            Player.movePlayer(gameBoard, boardSize, playerPositions, playerAmount, i, steps);

            if (checkVictory(playerPositions, playerAmount, boardSize - 1))
                isLastTile[i] = true;
        }

        round++;
    }

    /**
     *
     * Set end game results
     *
     */
    game->rounds = round;

    end(players, playerPositions, playerAmount, game);
}

void lastResults()
{
    FILE *file = fopen("storage/games.bin", "rb");

    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    GameInfo game;
    time_t currentTime = time(NULL);
    char date[100], gamePlayingDate[100];
    struct tm *currentDate = localtime(&currentTime);
    int currentDay = currentDate->tm_mday;
    int currentMonth = currentDate->tm_mon + 1;
    int currentYear = currentDate->tm_year + 1900;
    strftime(date, sizeof(date) - 1, "%d-%m-%Y", currentDate);
    int games = 0;

    printf("\n  Jogos nos ultimos "COLOR_Cyan"28 dias"COLOR_Default"\n\n");
    printf(COLOR_Blue "---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("  Data do jogo        \tRondas        \tDuração (m)    \tHora de inicio        \tHora de fim        \tVencedor\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);

    while (fread(&game, sizeof(game), 1, file) == 1)
    {
        int gameDay, gameMonth, gameYear, gameHourStart, gameMinuteStart, gameHourEnd, gameMinuteEnd;
        sscanf(game.gameDate, "%d-%d-%d", &gameDay, &gameMonth, &gameYear);
        sscanf(game.gameStartTime, "%d:%d", &gameHourStart, &gameMinuteStart);
        sscanf(game.gameEndTime, "%d:%d", &gameHourEnd, &gameMinuteEnd);

        int daysDifference = (currentYear - gameYear) * 365 + (currentMonth - gameMonth) * 30 + (currentDay - gameDay);

        if (daysDifference <= 28)
        {
            if (strcmp(game.gameDate, date) == 0)
                strcpy(gamePlayingDate, COLOR_Green "Hoje        " COLOR_Default);
            else
                strcpy(gamePlayingDate, game.gameDate);

            printf("  %-12s%-10s%-8d%-8s%-8d%-16s%-.2d:%-.2d%-19s%-.2d:%-.2d%-20s%-8s\n",
            gamePlayingDate, "", game.rounds, "", game.gameDuration, "", gameHourStart, gameMinuteStart, "", gameHourEnd, gameMinuteEnd, "", game.gameWinner.name);

            printf(COLOR_Blue"\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);
        }

        games++;
    }

    fclose(file);

    printf("\n A mostrar "COLOR_Green"%d"COLOR_Default" jogos\n\n", games);

    printf("\n\n\n");

    Screen.awaitInteraction();
}