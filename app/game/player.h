typedef struct Player
{
    int (*getPosition)(int *playerPositions, int currentPlayer);
    void (*movePlayer)(char gameBoard[], int boardSize, int *playerPositions, int playerAmount, int currentPlayer, int steps);
} PlayerController;

#include "player.c"