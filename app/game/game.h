typedef struct winnerInfo {
    char name[50];
    int correctAnswers;
    int wrongAnswers;
} WinnerInfo;

typedef struct gameInfo {
    int rounds;
    int gameDuration;
    char gameActions[400][100];
    char gameDate[25];
    char gameStartTime[35];
    char gameEndTime[35];
    WinnerInfo gameWinner;
} GameInfo;

typedef struct Game
{
    bool (*checkVictory)(int *playerPositions, int playerAmount, int lastSquare);
    void (*saveGame)(GameInfo *game);
    void (*end)(User *players[4], int *playerPositions, int playerAmount, GameInfo *game);
    void (*start)(User *players[4], int *playerPositions, int playerAmount, int boardSize);
    void (*lastResults)();
} GameController;

#include "game.c"