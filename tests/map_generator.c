#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct User
{
    char id[50], username[50], password[50], name[50], nationality[50], lastPlayingDate[20];
    int age;
    struct User *prev;
    struct User *next;
} User;

// Constants for board sizes and ASCII characters
#define BOARD_S 20
#define BOARD_M 30
#define BOARD_L 50
#define BOARD_WIDTH 10
#define GAMECH_VERTICAL '|'
#define GAMECH_HORIZONTAL '-'
#define GAMECH_QUESTION '?'
#define GAMECH_PLAYER_BASE 'P'

// Function to generate the game board
void generateGameBoard(char gameBoard[], int size)
{
    // Initialize the game board with empty spaces
    memset(gameBoard, ' ', size);

    // Place question marks on each square except the first
    for (int i = 1; i < size; i++)
    {
        gameBoard[i] = GAMECH_QUESTION;
    }
}

// Function to print the game board
void printGameBoard(const char gameBoard[], int size)
{
    // Print the top border
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        putchar(GAMECH_HORIZONTAL);
    }
    putchar('\n');

    // Print the game board rows
    for (int i = 0; i < size; i++)
    {
        putchar(GAMECH_VERTICAL);
        putchar(gameBoard[i]);
        if (i % BOARD_WIDTH == BOARD_WIDTH - 1)
        {
            putchar(GAMECH_VERTICAL);
            putchar('\n');
        }
    }

    // Print the bottom border
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        putchar(GAMECH_HORIZONTAL);
    }
    putchar('\n');
}

// Function to move a player on the game board
void movePlayer(char gameBoard[], int size, int *playerPositions, int playerAmount, int currentPlayer, int steps)
{
    // Get the current position of the player
    int currentPosition = playerPositions[currentPlayer];

    // Calculate the new position
    int newPosition = (currentPosition + steps) % size;

    // Update the game board with the new position of the player
    gameBoard[currentPosition] = ' ';
    gameBoard[newPosition] = GAMECH_PLAYER_BASE + currentPlayer;

    // Update the player's position
    playerPositions[currentPlayer] = newPosition;
}

// Function to check if any player has reached the last square
bool checkVictory(const int *playerPositions, int playerAmount, int lastSquare)
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
        boardSize = BOARD_S;
    }
    else if (strcmp(boardType, "M") == 0)
    {
        boardSize = BOARD_M;
    }
    else if (strcmp(boardType, "L") == 0)
    {
        boardSize = BOARD_L;
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

    // Allocate memory for the player positions array
    playerPositions = (int *)malloc(playerAmount * sizeof(int));

    // Initialize the player positions to the first square
    for (int i = 0; i < playerAmount; i++)
    {
        playerPositions[i] = 0;
    }

    // Create an array of User pointers for each player
    User *players[4] = {NULL};

    // Get the user information for each player
    for (int i = 0; i < playerAmount; i++)
    {
        User *newUser = (User *)malloc(sizeof(User));
        printf("\nEnter the information for player %d:\n", i + 1);
        printf("ID: ");
        scanf("%s", newUser->id);
        printf("Username: ");
        scanf("%s", newUser->username);
        printf("Password: ");
        scanf("%s", newUser->password);
        printf("Name: ");
        scanf("%s", newUser->name);
        printf("Nationality: ");
        scanf("%s", newUser->nationality);
        printf("Last Playing Date: ");
        scanf("%s", newUser->lastPlayingDate);
        printf("Age: ");
        scanf("%d", &(newUser->age));
        newUser->prev = NULL;
        newUser->next = NULL;

        // Assign the user to the corresponding player
        players[i] = newUser;
    }

    // Print the initial game board
    printf("\nInitial Game Board:\n");
    char gameBoard[boardSize];
    generateGameBoard(gameBoard, boardSize);
    printGameBoard(gameBoard, boardSize);

    // Game loop
    bool gameFinished = false;
    while (!gameFinished)
    {
        // Move each player by a random number of steps
        for (int i = 0; i < playerAmount; i++)
        {
            int steps;
            printf("\nPlayer %d: Enter the number of steps to move: ", i + 1);
            scanf("%d", &steps);

            // Move the player on the game board
            movePlayer(gameBoard, boardSize, playerPositions, playerAmount, i, steps);

            // Print the updated game board after moving the player
            printf("\nUpdated Game Board:\n");
            printGameBoard(gameBoard, boardSize);

            // Check if the player has won
            if (checkVictory(playerPositions, playerAmount, boardSize - 1))
            {
                printf("\nPlayer %d has won the game!\n", i + 1);
                gameFinished = true;
                break;
            }
        }
    }

    // Free the memory allocated for the player positions array
    free(playerPositions);

    // Free the memory allocated for the players' User structs
    for (int i = 0; i < playerAmount; i++)
    {
        free(players[i]);
    }

    return 0;
}
