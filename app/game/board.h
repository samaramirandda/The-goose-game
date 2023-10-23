// Sizes
#define BOARD_0 0
#define BOARD_S 20
#define BOARD_M 30
#define BOARD_L 50

// Width
#define BOARD_WIDTH 10

typedef struct boardController
{
    int (*getBoardSize)();
    void (*generateGameBoard)(char gameBoard[], int size);
    void (*printGameBoard)(char gameBoard[], int *playerPositions, int playerAmount, int size);
} BoardController;

#include "board.c"