void title(char title[])
{
    printf(COLOR_Red TL LINE TR);
    printf("\n");
    printf("\n%s", title);
    printf("\n\n");
    printf(BL LINE BR "\n\n");
}

void menu(char *options[], int quantity, bool prompt)
{
    for (int i = 0; i < quantity; i++)
        printf(COLOR_Cyan "  [" COLOR_Green "%d" COLOR_Cyan "]" COLOR_Default " %s\n\n", i + 1, options[i]);

    printf(COLOR_Cyan "  [" COLOR_Green "0" COLOR_Cyan "]" COLOR_Default " Sair\n\n");

    if (prompt)
        printf(COLOR_Cyan "  [" COLOR_Green "»" COLOR_Cyan "]" COLOR_Default " ");
}

char getOS()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        return 'W';
    #elif __APPLE__
        return 'A';
    #elif __linux__
        return 'U';
    #elif __unix__
        return 'U';
    #elif defined(_POSIX_VERSION)
        return 'U';
    #endif
}

void clear()
{
    char OS = getOS();
    char temp;
    
    switch(OS) {
        case 'W': 
            system("cls");
            break;

        case 'A':
            system("clear");
            break;

        case 'U':
            system("clear");
            break;
    }
}

void awaitInteraction()
{
    char OS = getOS();
    char temp;

    switch(OS) {
        case 'W': 
            system("pause");  
            break;

        case 'A':
            system( "read -n 1 -s -p \"Pressione qualquer tecla para prosseguir..\"");
            break;

        case 'U':
            printf(COLOR_Yellow"\nDigite qualquer caracter para continuar...");
            fflush(stdin);
            scanf("%c", &temp);
            break;
    }
}