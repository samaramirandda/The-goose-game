bool userExists(char username[])
{
    User *current = firstUser;

    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
            return true;

        current = current->next;
    }

    return false;
}

bool isUserAdmin(char username[])
{
    User *current = firstUser;

    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
            return current->isAdmin;

        current = current->next;
    }

    return false;
}

bool isLoggedIn(User *user)
{
    return user->loggedIn;
}

User *getUserByUsername(char username[])
{
    User *current = firstUser;

    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
            return current;

        current = current->next;
    }

    return NULL;
}

void insertUserAtEnd(User *newUser)
{
    if (firstUser == NULL)
        firstUser = newUser;
    else
    {
        User *temp = firstUser;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newUser;
        newUser->id = temp->id + 1;
        newUser->prev = temp;
    }
}

void saveUserToFile(User *user)
{
    char line[254];
    sprintf(line, "%s;%s;%s;%d;%s;%s;%s", user->username, user->password, user->name, user->age, user->nationality, (user->lastPlayingDate[0] == '\0') ? "0" : user->lastPlayingDate, (user->isAdmin) ? "true" : "false");
    Storage.appendFile("users.accounts", line);
}

void importUsersFromFile()
{
    FILE *file = fopen("storage/users.accounts", "r");

    if (file == NULL)
        return;

    if (Storage.isEmptyFile("users.accounts"))
        return;

    firstUser = NULL;

    while (!feof(file))
    {
        User *newUser = (User *)malloc(sizeof(User));
        char isAdmin[10];

        int i = 1, scan;

        scan = fscanf(file, " %[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^\n]",
                      newUser->username, newUser->password,
                      newUser->name, &(newUser->age), newUser->nationality,
                      newUser->lastPlayingDate, isAdmin);

        if (scan)
        {
            if (newUser->lastPlayingDate[0] == '0')
                newUser->lastPlayingDate[0] = '\0';

            if (strcmp(isAdmin, "true") == 0)
                newUser->isAdmin = true;
            else
                newUser->isAdmin = false;

            newUser->loggedIn = false;

            newUser->next = NULL;
            newUser->prev = NULL;

            newUser->id = i;

            if (firstUser == NULL)
            {
                firstUser = newUser;
            }
            else
            {
                User *current = firstUser;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newUser;
                newUser->prev = current;
            }

            i++;
        }
        else
        {
            free(newUser);
        }
    }

    fclose(file);
}

void refreshUsersFile()
{
    Storage.clearFile("users.accounts");

    User *current = firstUser;
    while (current != NULL)
    {
        char line[254];
        sprintf(line, "%s;%s;%s;%d;%s;%s;%s", current->username, current->password, current->name, current->age, current->nationality, (current->lastPlayingDate[0] == '\0') ? "0" : current->lastPlayingDate, (current->isAdmin) ? "true" : "false");
        Storage.appendFile("users.accounts", line);
        current = current->next;
    }
}

void createUser(char username[], char password[], char name[], int age, char nationality[], char lastPlayingDate[], bool isAdmin)
{
    char tempAge[5];
    User *newUser = (User *)malloc(sizeof(User));

    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    strcpy(newUser->name, name);
    newUser->age = age;
    strcpy(newUser->nationality, nationality);
    strcpy(newUser->lastPlayingDate, lastPlayingDate);
    Functions.toString(tempAge, age);
    newUser->isAdmin = isAdmin;
    newUser->loggedIn = false;

    newUser->next = NULL;
    newUser->prev = NULL;

    insertUserAtEnd(newUser);
    saveUserToFile(newUser);
}

void registerUser()
{
    if (Screen.getOS() == 'U')
    {
        char tempC;
        scanf("%c", &tempC);
    }

    if (Storage.lines("users.accounts") == 99)
    {
        Screen.clear();
        Exceptions.setError("O maximo de utilizadores foi atingido! A abortar...");
        Exceptions.printError();
    }

    char username[50], password[50], tempPassword[50], name[50], nationality[50], lastPlayingDate[50];
    int age;

    do
    {
        if (error)
        {
            Screen.clear();
            Exceptions.printError();
        }

        fflush(stdin);
        printf(COLOR_Blue "> Username: " COLOR_Default);
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        if (userExists(username))
            Exceptions.setError("Um utilizador com esse username já existe!");
    } while (userExists(username));

    do
    {
        if (error)
        {
            Screen.clear();
            Exceptions.printError();
        }

        printf(COLOR_Blue "\n> Password: " COLOR_Default);
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        printf(COLOR_Blue "\n> Confirme a password: " COLOR_Default);
        fgets(tempPassword, sizeof(tempPassword), stdin);
        tempPassword[strcspn(tempPassword, "\n")] = '\0';

        if (strcmp(password, tempPassword) != 0)
            Exceptions.setError("As passwords não coincidem. Por favor, tente novamente!");

    } while (strcmp(password, tempPassword) != 0);

    printf(COLOR_Blue "\n> Nome: " COLOR_Default);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf(COLOR_Blue "\n> Idade: " COLOR_Default);
    scanf("%d", &age);
    getchar();

    printf(COLOR_Blue "\n> Nacionalidade: " COLOR_Default);
    fgets(nationality, sizeof(nationality), stdin);
    nationality[strcspn(nationality, "\n")] = '\0';

    bool isAdmin;

    if (isUserAdmin(adminUser->username))
    {
        char isAdminTemp;
        printf(COLOR_Blue "\n> O utilizador é administrador (S/N)? " COLOR_Default);
        isAdminTemp = getchar();
        (isAdminTemp == 'S') ? (isAdmin = true) : (isAdmin = false);
    }
    else
    {
        isAdmin = false;
    }

    lastPlayingDate[0] = '\0';

    Screen.clear();
    printf(COLOR_Green "Utilizador criado com sucesso! \nA retomar...\n\n" COLOR_Default);
    createUser(username, password, name, age, nationality, lastPlayingDate, isAdmin);
}

void removeUser()
{
    if (Screen.getOS() == 'U')
    {
        char tempC;
        scanf("%c", &tempC);
    }

    if (firstUser == NULL || Storage.lines("users.accounts") == -1)
    {
        Screen.clear();
        Exceptions.setError("Nenhum utilizador foi ainda criado. É necessário criar um utilizador para poder removê-lo.");
        Exceptions.printError();
        return;
    }

    char username[50];

    do
    {
        if (error)
        {
            Screen.clear();
            Exceptions.printError();
        }

        fflush(stdin);
        printf(COLOR_Blue "> Username do utilizador remover: " COLOR_Default);
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        if (!userExists(username))
            Exceptions.setError("Nenhum utilizador com esse username não existe!");

        if (strcmp(username, adminUser->username) == 0)
            Exceptions.setError("Não podes eliminar a tua própria conta!");

    } while (error);

    if (firstUser == NULL)
    {
        // The list is empty
        return;
    }

    User *current = firstUser;

    // Find the user with the specified username
    while (current != NULL && strcmp(current->username, username) != 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        // User not found in the list
        return;
    }

    if (current->prev == NULL)
    {
        // The user to be removed is the first user in the list
        firstUser = current->next;
        if (firstUser != NULL)
        {
            (firstUser)->prev = NULL;
        }
    }
    else
    {
        // The user to be removed is not the first user in the list
        current->prev->next = current->next;
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }

    // Free the memory occupied by the user
    free(current);

    // Remove from the users file
    refreshUsersFile();
}

bool checkLogin(char username[], char password[])
{
    if (!userExists(username))
        return false;

    User *current = firstUser;

    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
            if (strcmp(current->password, password) == 0)
                if (isLoggedIn(current))
                    return false;
                else
                    return true;

        current = current->next;
    }

    return false;
}

User *login()
{
    if (Screen.getOS() == 'U')
    {
        char tempC;
        scanf("%c", &tempC);
    }

    if (firstUser == NULL || Storage.lines("users.accounts") == -1)
    {
        char createUser;

        Screen.clear();
        Exceptions.setError("Nenhum utilizador foi ainda criado. Deseja criar um? (S/N) ");
        Exceptions.printError();
        printf(COLOR_Blue "\n> " COLOR_Default);
        createUser = getchar();

        if (createUser == 'S')
        {
            registerUser();
        }
        else
        {
            return NULL;
        }
    }

    char username[50], password[50];

    do
    {
        Screen.title("\tPor favor, autentique-se!");

        if (error)
        {
            Screen.clear();
            Exceptions.printError();
        }

        fflush(stdin);
        printf(COLOR_Blue "> Username: " COLOR_Default);
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        if (!userExists(username))
        {
            char createUser;
            Screen.clear();
            Exceptions.setError("Nenhum utilizador com esse username foi criado. Deseja criar um? (S/N) ");
            Exceptions.printError();
            printf(COLOR_Blue "\n> " COLOR_Default);
            createUser = getchar();

            if (createUser == 'S')
            {
                registerUser();
            }
        }

        fflush(stdin);
        printf(COLOR_Blue "> Password: " COLOR_Default);
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        if (!checkLogin(username, password))
            Exceptions.setError("O utilizador ou password não estão corretos ou o utilizador já está em uso!");
    } while (!checkLogin(username, password));

    User *temp = getUserByUsername(username);
    temp->loggedIn = true;

    return temp;
}

User *logout(User *user)
{
    if (user->loggedIn == false)
        return NULL;

    user->loggedIn = false;
    
    return NULL;
}

void adminLogout()
{
    if (adminUser == NULL)
        return;

    adminUser = NULL;
}

void adminLogin()
{
    if (Screen.getOS() == 'U')
    {
        char tempC;
        scanf("%c", &tempC);
    }

    if (firstUser == NULL || Storage.lines("users.accounts") == -1)
    {
        Screen.clear();
        Exceptions.setError("Nenhum utilizador foi ainda criado. É necessário criar um utilizador para poder se autenticar!");
        Exceptions.printError();
        return;
    }

    char username[50], password[50];

    do
    {
        Screen.title("\tPor favor, autentique-se!");

        if (error)
        {
            Screen.clear();
            Exceptions.printError();
        }

        fflush(stdin);
        printf(COLOR_Blue "> Username: " COLOR_Default);
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        fflush(stdin);
        printf(COLOR_Blue "> Password: " COLOR_Default);
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        if (!checkLogin(username, password))
            Exceptions.setError("O utilizador ou password não estão corretos!");
    } while (!checkLogin(username, password));

    adminUser = getUserByUsername(username);

    if (!isUserAdmin(username))
    {
        Screen.clear();
        Exceptions.setError("Não tens permissão para aceder a esta página. A sair...");
        Exceptions.printError();
        adminLogout();
        Screen.awaitInteraction();
        return;
    }
}

int compareUsersByUsername(User *user1, User *user2)
{
    return strcmp(user1->username, user2->username);
}

void insertionSortUsersByUsername()
{
    if (firstUser == NULL || firstUser->next == NULL)
        return;

    User *sorted = NULL;        // Sorted part of the list
    User *unsorted = firstUser; // Unsorted part of the list

    while (unsorted != NULL)
    {
        User *current = unsorted;
        unsorted = unsorted->next;

        if (sorted == NULL || compareUsersByUsername(current, sorted) < 0)
        {
            // Insert the current user at the beginning of the sorted list
            current->next = sorted;
            current->prev = NULL;
            if (sorted != NULL)
            {
                sorted->prev = current;
            }
            sorted = current;
        }
        else
        {
            // Find the correct position to insert the current user in the sorted list
            User *temp = sorted;
            while (temp->next != NULL && compareUsersByUsername(current, temp->next) >= 0)
            {
                temp = temp->next;
            }

            // Insert the current user after temp in the sorted list
            current->next = temp->next;
            current->prev = temp;
            if (temp->next != NULL)
            {
                temp->next->prev = current;
            }
            temp->next = current;
        }
    }

    // Update the firstUser pointer to the sorted list
    firstUser = sorted;
}

void insertionSortUsersByAge()
{
    if (firstUser == NULL || firstUser->next == NULL)
        // The list is empty or contains only one element
        return;

    User *sorted = NULL;        // Sorted part of the list
    User *unsorted = firstUser; // Unsorted part of the list

    while (unsorted != NULL)
    {
        User *current = unsorted;
        unsorted = unsorted->next;

        if (sorted == NULL || current->age > sorted->age)
        {
            // Insert the current user at the beginning of the sorted list
            current->next = sorted;
            current->prev = NULL;
            if (sorted != NULL)
            {
                sorted->prev = current;
            }
            sorted = current;
        }
        else
        {
            // Find the correct position to insert the current user in the sorted list
            User *temp = sorted;
            while (temp->next != NULL && temp->next->age > current->age)
            {
                temp = temp->next;
            }

            // Insert the current user after temp in the sorted list
            current->next = temp->next;
            current->prev = temp;
            if (temp->next != NULL)
            {
                temp->next->prev = current;
            }
            temp->next = current;
        }
    }

    // Update the firstUser pointer to the sorted list
    firstUser = sorted;
}

void insertionSortUsersByLastPlayingDate()
{
    if (firstUser == NULL || firstUser->next == NULL)
        // The list is empty or contains only one element
        return;

    User *sorted = NULL;        // Sorted part of the list
    User *unsorted = firstUser; // Unsorted part of the list

    while (unsorted != NULL)
    {
        User *current = unsorted;
        unsorted = unsorted->next;

        if (sorted == NULL || compareDates(current->lastPlayingDate, sorted->lastPlayingDate) > 0)
        {
            // Insert the current user at the beginning of the sorted list
            current->next = sorted;
            current->prev = NULL;
            if (sorted != NULL)
            {
                sorted->prev = current;
            }
            sorted = current;
        }
        else
        {
            // Find the correct position to insert the current user in the sorted list
            User *temp = sorted;
            while (temp->next != NULL && compareDates(temp->next->lastPlayingDate, current->lastPlayingDate) > 0)
            {
                temp = temp->next;
            }

            // Insert the current user after temp in the sorted list
            current->next = temp->next;
            current->prev = temp;
            if (temp->next != NULL)
            {
                temp->next->prev = current;
            }
            temp->next = current;
        }
    }

    // Update the firstUser pointer to the sorted list
    firstUser = sorted;
}

void displayUsers()
{
    int option, filter = 0;

    if (firstUser == NULL)
    {
        Exceptions.setError("A lista de utilizadores esta vazia. Por favor, registe um utilizador primeiro!");
        Exceptions.printError();
        Screen.awaitInteraction();
        return;
    }

    User *temp = firstUser;

    do
    {

        Screen.clear();

        if (error)
            Exceptions.printError();

        printf(COLOR_Blue "---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("  ID        \tUsername        \tPassword        \tNome            \tIdade   \tNacionalidade   \tUltima data de jogo\n");
        printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);

        switch (filter)
        {
        // No filter
        default:
            temp = firstUser;
            while (temp != NULL)
            {
                char date[100], lastPlayingDate[35];
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                strftime(date, sizeof(date) - 1, "%d-%m-%Y", t);

                if (strcmp(temp->lastPlayingDate, date) == 0)
                    strcpy(lastPlayingDate, COLOR_Green "Hoje");
                else
                    strcpy(lastPlayingDate, temp->lastPlayingDate);

                printf("  %-8d\t%-8s\t\t%-8s\t\t%-16s\t%-8d\t%-16s\t" COLOR_Cyan "%-8s", temp->id, temp->username, temp->password, temp->name, temp->age, temp->nationality, (temp->lastPlayingDate[0] == '\0') ? COLOR_Red "Nunca jogou" COLOR_Default : lastPlayingDate);
                printf(COLOR_Blue "\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);
                temp = temp->next;
            }
            break;

        // Alphabetical order
        case 1:
            insertionSortUsersByUsername();
            temp = firstUser;

            while (temp != NULL)
            {
                char date[100], lastPlayingDate[35];
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                strftime(date, sizeof(date) - 1, "%d-%m-%Y", t);

                if (strcmp(temp->lastPlayingDate, date) == 0)
                    strcpy(lastPlayingDate, COLOR_Green "Hoje");
                else
                    strcpy(lastPlayingDate, temp->lastPlayingDate);

                printf("  %-8d\t%-8s\t\t%-8s\t\t%-16s\t%-8d\t%-16s\t" COLOR_Cyan "%-8s", temp->id, temp->username, temp->password, temp->name, temp->age, temp->nationality, (temp->lastPlayingDate[0] == '\0') ? COLOR_Red "Nunca jogou" COLOR_Default : lastPlayingDate);
                printf(COLOR_Blue "\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);
                temp = temp->next;
            }
            break;

        // Desc, age
        case 2:
            insertionSortUsersByAge();
            temp = firstUser;
            while (temp != NULL)
            {
                char date[100], lastPlayingDate[35];
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                strftime(date, sizeof(date) - 1, "%d-%m-%Y", t);

                if (strcmp(temp->lastPlayingDate, date) == 0)
                    strcpy(lastPlayingDate, COLOR_Green "Hoje");
                else
                    strcpy(lastPlayingDate, temp->lastPlayingDate);

                printf("  %-8d\t%-8s\t\t%-8s\t\t%-16s\t%-8d\t%-16s\t" COLOR_Cyan "%-8s", temp->id, temp->username, temp->password, temp->name, temp->age, temp->nationality, (temp->lastPlayingDate[0] == '\0') ? COLOR_Red "Nunca jogou" COLOR_Default : lastPlayingDate);
                printf(COLOR_Blue "\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);

                temp = temp->next;
            }
            break;

        // Desc, lastPlayingDate
        case 3:
            insertionSortUsersByLastPlayingDate();
            temp = firstUser;
            while (temp != NULL)
            {
                char date[100], lastPlayingDate[35];
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                strftime(date, sizeof(date) - 1, "%d-%m-%Y", t);

                if (strcmp(temp->lastPlayingDate, date) == 0)
                    strcpy(lastPlayingDate, COLOR_Green "Hoje");
                else
                    strcpy(lastPlayingDate, temp->lastPlayingDate);

                printf("  %-8d\t%-8s\t\t%-8s\t\t%-16s\t%-8d\t%-16s\t" COLOR_Cyan "%-8s", temp->id, temp->username, temp->password, temp->name, temp->age, temp->nationality, (temp->lastPlayingDate[0] == '\0') ? COLOR_Red "Nunca jogou" COLOR_Default : lastPlayingDate);
                printf(COLOR_Blue "\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);

                temp = temp->next;
            }
            break;
        }

        printf("\n\n");
        printf("\t[0] Sair   |   [1] Ordenar por ordem alfabética   |   [2] Ordenar por idade decrescente   |   [3] Ordenar por data de jogo");
        printf("\n\n> ");
        scanf("%d", &option);
        switch (option)
        {
        case 0:
            filter = 0;
            break;
        case 1:
            filter = 1;
            break;

        case 2:
            filter = 2;
            break;

        case 3:
            filter = 3;
            break;

        default:
            Exceptions.setError("Opção inválida. Por favor faça uma escolha com uma das opções disponíveis!\n\n");
            filter = 0;
            break;
        }
    } while (option != 0);
}

void displayPlayers(User *player1, User *player2, User *player3, User *player4)
{
    if (player1 == NULL)
    {
        Exceptions.setError("Erro ao listar jogadores.");
        Exceptions.printError();
        Screen.awaitInteraction();
        return;
    }

    printf(COLOR_Blue "---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("  ID        \tUsername        \tPassword        \tNome            \tIdade   \tNacionalidade   \tUltima data de jogo\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);

    printf("  %-8d\t%-8s\t\t%-8s\t\t%-16s\t%-8d\t%-16s\t%-8s\n", player1->id, player1->username, "(Protegido)", player1->name, player1->age, player1->nationality, (player1->lastPlayingDate[0] == '\0') ? COLOR_Red "Nunca jogou" COLOR_Default : player1->lastPlayingDate);
    printf(COLOR_Blue "\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);

    if (player2 != NULL)
    {
        printf("  %-8d\t%-8s\t\t%-8s\t\t%-16s\t%-8d\t%-16s\t%-8s\n", player2->id, player2->username, "(Protegido)", player2->name, player2->age, player2->nationality, (player2->lastPlayingDate[0] == '\0') ? COLOR_Red "Nunca jogou" COLOR_Default : player2->lastPlayingDate);
        printf(COLOR_Blue "\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);
    }

    if (player3 != NULL)
    {
        printf("  %-8d\t%-8s\t\t%-8s\t\t%-16s\t%-8d\t%-16s\t%-8s\n", player3->id, player3->username, "(Protegido)", player3->name, player3->age, player3->nationality, (player3->lastPlayingDate[0] == '\0') ? COLOR_Red "Nunca jogou" COLOR_Default : player3->lastPlayingDate);
        printf(COLOR_Blue "\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);
    }

    if (player4 != NULL)
    {
        printf("  %-8d\t%-8s\t\t%-8s\t\t%-16s\t%-8d\t%-16s\t%-8s\n", player4->id, player4->username, "(Protegido)", player4->name, player4->age, player4->nationality, (player4->lastPlayingDate[0] == '\0') ? COLOR_Red "Nunca jogou" COLOR_Default : player4->lastPlayingDate);
        printf(COLOR_Blue "\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" COLOR_Default);
    }
}

void updatePlayingDate(User *players[4], int playerAmount)
{
    char date[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(date, sizeof(date) - 1, "%d-%m-%Y", t);

    for (int i = 0; i < playerAmount; i++)
        strcpy(players[i]->lastPlayingDate, date);

    refreshUsersFile();
}

void freeUsers()
{
    User *temp;
    while (firstUser != NULL)
    {
        temp = firstUser;
        firstUser = firstUser->next;
        free(temp);
    }
}