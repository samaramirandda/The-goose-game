int lines(char fileName[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);
    FILE *file = fopen(path, "r");

    if (file == NULL)
        return -1;

    int lines = 0;
    char c;
    while (!feof(file))
    {
        c = fgetc(file);
        if (c == '\n')
            lines++;
    }

    fclose(file);

    return lines;
}

void createFile(char fileName[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);
    FILE *file = fopen(path, "w");

    if (file == NULL)
    {
        Exceptions.setError("Ocorreu um erro ao criar o ficheiro. Por favor, tente novamente mais tarde!");
        Exceptions.printError();
        return;
    }

    fclose(file);
}

bool isEmptyFile(char fileName[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        Exceptions.setError("Ocorreu um erro ao ler o ficheiro. Por favor, tente novamente mais tarde!");
        Exceptions.printError();
        return 0;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        fclose(file);
        return true;
    }

    fclose(file);
    return false;
}

void appendFile(char fileName[], char text[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);
    FILE *file = fopen(path, "a");

    if (file == NULL)
    {
        Exceptions.setError("Ocorreu um erro ao abrir/criar o ficheiro. Por favor, tente novamente mais tarde!");
        Exceptions.printError();
        return;
    }

    fprintf(file, "%s%s", (isEmptyFile(fileName) && lines(fileName) == 0) ? "" : "\n", text);

    fclose(file);
}

void writeFile(char fileName[], char text[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);
    FILE *file = fopen(path, "w");

    if (file == NULL)
    {
        Exceptions.setError("Ocorreu um erro ao abrir/criar o ficheiro. Por favor, tente novamente mais tarde!");
        Exceptions.printError();
        return;
    }

    fprintf(file, "%s", text);

    fclose(file);
}

void removeFile(char fileName[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);
    remove(path);
}

void clearFile(char fileName[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);
    FILE *file = fopen(path, "w+");

    if (file == NULL)
    {
        Exceptions.setError("Ocorreu um erro ao abrir/criar o ficheiro. Por favor, tente novamente mais tarde!");
        Exceptions.printError();
        return;
    }

    fclose(file);
}

void renameFile(char fileName[], char newFileName[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);
    char newPath[50];
    strcpy(newPath, "storage/");
    strcat(newPath, newFileName);

    rename(path, newPath);
}

void copyFile(char fileName[], char newFileName[])
{
    char path[50];
    strcpy(path, "storage/");
    strcat(path, fileName);

    FILE *file = fopen(path, "w+");

    if (file == NULL)
    {
        Exceptions.setError("Ocorreu um erro ao ler o ficheiro para ser copiado. Por favor, tente novamente mais tarde!");
        Exceptions.printError();
        return;
    }

    char newPath[50];
    strcpy(newPath, "storage/");
    strcat(newPath, newFileName);

    FILE *newFile = fopen(newPath, "w+");

    if (newFile == NULL)
    {
        Exceptions.setError("Ocorreu um erro ao ler o ficheiro para copia. Por favor, tente novamente mais tarde!");
        Exceptions.printError();
        return;
    }

    int character;
    while ((character = fgetc(file)) != EOF)
    {
        fputc(character, newFile);
    }

    fclose(file);
    fclose(newFile);
}