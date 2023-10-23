#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for board sizes and ASCII characters
#define BOARD_SIZE_S 20
#define BOARD_SIZE_M 30
#define BOARD_SIZE_L 50
#define BOARD_WIDTH 10
#define ASCII_VERTICAL '|'
#define ASCII_HORIZONTAL '-'
#define PLAYER '1'
#define ASCII_QUESTION ' '

// Function to generate the game board
void generateGameBoard(char gameBoard[], int size)
{
    // Initialize the game board with empty spaces
    memset(gameBoard, ' ', size);

    // Place question marks on each square except the first
    for (int i = 1; i < size; i++)
    {
        gameBoard[i] = ASCII_QUESTION;
    }
}

// Function to print the game board
void printGameBoard(const char gameBoard[], int size)
{
    // Print the top border
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        putchar(ASCII_HORIZONTAL);
    }
    putchar('\n');

    // Print the game board rows
    for (int i = 0; i < size; i++)
    {
        putchar(ASCII_VERTICAL);
        putchar(gameBoard[i]);
        if (i % BOARD_WIDTH == BOARD_WIDTH - 1)
        {
            putchar(ASCII_VERTICAL);
            putchar('\n');
        }
    }

    // Print the bottom border
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        putchar(ASCII_HORIZONTAL);
    }
    putchar('\n');
}

// Function to move a player on the game board
void movePlayer(char gameBoard[], int size, int *playerPositions, int playerAmount, int playerIndex, int steps)
{
    // Get the current position of the player
    int currentPosition = playerPositions[playerIndex];

    // Calculate the new position
    int newPosition = (currentPosition + steps) % size;

    // Update the game board with the new position of the player
    gameBoard[currentPosition] = ' ';
    gameBoard[newPosition] = PLAYER + playerIndex;

    // Update the player's position
    playerPositions[playerIndex] = newPosition;
}

int main()
{
    // Variables to hold the board size, game board, and player positions
    int boardSize;
    char boardType[2];
    int playerAmount;
    int *playerPositions;

    // Get the board type from the user
    printf("Enter the board type (S, M, or L): ");
    scanf("%s", boardType);

    // Determine the board size based on the input
    if (strcmp(boardType, "S") == 0)
    {
        boardSize = BOARD_SIZE_S;
    }
    else if (strcmp(boardType, "M") == 0)
    {
        boardSize = BOARD_SIZE_M;
    }
    else if (strcmp(boardType, "L") == 0)
    {
        boardSize = BOARD_SIZE_L;
    }
    else
    {
        printf("Invalid board type!\n");
        return 1;
    }

    // Get the number of players from the user
    printf("Enter the number of players (1-4): ");
    scanf("%d", &playerAmount);

    // Check if the player count is within the valid range
    if (playerAmount < 1 || playerAmount > 4)
    {
        printf("Invalid number of players!\n");
        return 1;
    }

    // Create an array to hold the game board
    char gameBoard[boardSize];

    // Generate the game board
    generateGameBoard(gameBoard, boardSize);

    // Allocate memory for the player positions array
    playerPositions = (int *)malloc(playerAmount * sizeof(int));

    // Initialize the player positions to the first square
    for (int i = 0; i < playerAmount; i++)
    {
        playerPositions[i] = 0;
    }

    // Print the initial game board
    printGameBoard(gameBoard, boardSize);

    // Move each player by a random number of steps
    for (int i = 0; i < playerAmount; i++)
    {
        int steps;
        printf("Enter the number of steps for player %d: ", i + 1);
        scanf("%d", &steps);

        // Move the player on the game board
        movePlayer(gameBoard, boardSize, playerPositions, playerAmount, i, steps);

        // Print the updated game board after moving the player
        printGameBoard(gameBoard, boardSize);
    }

    // Free the memory allocated for the player positions array
    free(playerPositions);

    return 0;
}
