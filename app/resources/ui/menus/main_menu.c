/*
 *
 * @name Main Menu
 * @brief This function generates the main menu where all the program will be ran on
 * @author João Ferreira and Samara Miranda
 *
 * */
void mainMenu()
{
    int loginOption, adminOption, manageQuestionsOption, manageUsersOption;
    int playerAmount;
    char *loginOptions[2] = {"Jogar", "Administrar"};
    char *adminOptions[3] = {"Gerir perguntas", "Gerir Utilizadores", "Ultimos jogos"};
    char *manageQuestionsOptions[3] = {"Criar pergunta", "Remover pergunta", "Listar perguntas"};
    char *manageUsersOptions[3] = {"Registar utilizador", "Remover utilizador", "Listar utilizadores"};

    Screen.clear();

    while (loginOption != 0)
    {
        Screen.clear();

        Screen.title("      Deseja jogar ou administrar?");

        if (error)
            Exceptions.printError(error);

        Screen.menu(loginOptions, 2, true);
        scanf("%d", &loginOption);

        switch (loginOption)
        {
        case 1:
            if (firstUser == NULL)
            {
                Exceptions.setError("Por favor, registe pelo menos um utilizador para poder jogar!");
                break;
            }

            do
            {
                Screen.clear();

                Screen.title("\t\tBEM-VINDO");

                if (error)
                    Exceptions.printError();

                printf(COLOR_Blue "\n> Quantos jogadores vão jogar? (1 - 4): " COLOR_Default);
                scanf("%d", &playerAmount);
                getchar();

                if (playerAmount > 4 || playerAmount < 1)
                    Exceptions.setError("Por favor, indique uma quantidade de jogadores válida!");
            } while (playerAmount > 4 || playerAmount < 1);

            int *playerPositions = (int *)malloc(playerAmount * sizeof(int));

            for (int i = 0; i < playerAmount; i++)
                playerPositions[i] = 0;
            
            for (int i = playerAmount; i < 4; i++)
                playerPositions[i] = -1;

            User *players[4] = {NULL};

            for (int i = 0; i < playerAmount; i++)
            {
                Screen.clear();
                switch (i)
                {
                case 0:
                    players[0] = firstPlayer = Users.login();
                    break;

                case 1:
                    players[1] = secondPlayer = Users.login();
                    break;

                case 2:
                    players[2] = thirdPlayer = Users.login();
                    break;

                case 3:
                    players[3] = fourthPlayer = Users.login();
                    break;
                }
            }

            Screen.clear();
            Screen.title("\t\tCONFIRMAÇÃO");

            Users.displayPlayers(firstPlayer, secondPlayer, thirdPlayer, fourthPlayer);

            int confirmation;
            printf(COLOR_Blue "\n\n> Confirmar jogadores? (1 - Confirmar | 2 - Cancelar)\n- " COLOR_Default);
            scanf("%d", &confirmation);

            if (confirmation == 2)
            {
                if(players[0] != NULL)
                    players[0] = firstPlayer = Users.logout(firstPlayer);

                if(players[1] != NULL)
                    players[1] = secondPlayer = Users.logout(secondPlayer);

                if(players[2] != NULL)
                    players[2] = thirdPlayer = Users.logout(thirdPlayer);

                if(players[3] != NULL)
                    players[3] = fourthPlayer = Users.logout(fourthPlayer);
                break;
            }

            int boardSize = Board.getBoardSize();

            Game.start(players, playerPositions, playerAmount, boardSize);

            break;

        case 2:
            Screen.clear();

            if (firstUser == NULL)
            {
                Exceptions.setError("Por favor, registe pelo menos um utilizador pelo sistema interno para poder administrar!");
                break;
            }

            if (adminUser == NULL)
                Users.adminLogin();

            if (adminUser == NULL)
                break;

            do
            {
                Screen.clear();
                char menuTitle[254];
                sprintf(menuTitle, "\t\tBEM-VINDO, %s", adminUser->name);
                Screen.title(menuTitle);
                Screen.menu(adminOptions, 3, true);
                scanf("%d", &adminOption);

                switch (adminOption)
                {
                case 1:
                    Screen.clear();

                    Screen.title("\tGERIR PERGUNTAS");

                    if (error)
                        Exceptions.printError(error);

                    Screen.menu(manageQuestionsOptions, 3, true);
                    scanf("%d", &manageQuestionsOption);

                    switch (manageQuestionsOption)
                    {
                    case 1:
                        Screen.clear();
                        Questions.newQuestion();
                        Screen.awaitInteraction();
                        break;

                    case 2:
                        Questions.removeQuestion();
                        break;

                    case 3:
                        Questions.listQuestions();
                        break;

                    default:
                        Exceptions.setError("Opção inválida. Por favor faça uma escolha com uma das opções disponíveis!\n\n");
                        break;

                    case 0:
                        break;
                    }
                    break;

                case 2:
                    do
                    {
                        Screen.clear();

                        Screen.title("\tGERIR UTILIZADORES");

                        if (error)
                            Exceptions.printError(error);

                        Screen.menu(manageUsersOptions, 3, true);
                        scanf("%d", &manageUsersOption);

                        switch (manageUsersOption)
                        {
                        case 1:
                            Screen.clear();
                            Users.registerUser();
                            Screen.awaitInteraction();
                            break;

                        case 2:
                            Screen.clear();
                            Users.removeUser();
                            Screen.awaitInteraction();
                            break;

                        case 3:
                            Screen.clear();
                            Users.displayUsers();
                            break;

                        default:
                            Exceptions.setError("Opção inválida. Por favor faça uma escolha com uma das opções disponíveis!\n\n");
                            break;

                        case 0:
                            break;
                        }
                    } while (manageUsersOption != 0);
                    break;
                
                case 3:
                    Screen.clear();
                    Game.lastResults();
                    break;

                default:
                    Exceptions.setError("Opção inválida. Por favor faça uma escolha com uma das opções disponíveis!\n\n");
                    break;

                case 0:
                    Users.adminLogout();
                    break;
                }
            } while (adminOption != 0);
            break;

        default:
            Screen.clear();
            Exceptions.setError("Opção inválida. Por favor faça uma escolha com uma das opções disponíveis!\n\n");
            break;

        case 0:
            Screen.clear();
            exit(1);
            break;
        }
    }
}
