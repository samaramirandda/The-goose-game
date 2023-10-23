int getPosition(int *playerPositions, int currentPlayer)
{
    return playerPositions[currentPlayer];
}

void movePlayer(char gameBoard[], int boardSize, int *playerPositions, int playerAmount, int currentPlayer, int steps)
{
    if (currentPlayer < 0 || currentPlayer >= playerAmount)
    {
        Exceptions.setError("Ocorreu um erro: Indice de jogador inválido.");
        Exceptions.printError();
        return;
    }

    int currentPosition = playerPositions[currentPlayer];
    int newPosition = playerPositions[currentPlayer] + steps;

    if (newPosition >= boardSize)
    {
        playerPositions[currentPlayer] = boardSize - 1;
        return;
    }

    gameBoard[currentPosition] = ' ';
    gameBoard[newPosition] = GAMECH_PLAYER_BASE + currentPlayer;

    playerPositions[currentPlayer] = newPosition;
}