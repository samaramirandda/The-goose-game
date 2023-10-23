bool questionExists(int id)
{
    Question *current = firstQuestion;

    while (current != NULL)
    {
        if (current->id == id)
            return true;

        current = current->next;
    }

    return false;
}

Question *createQuestion(char question[], QuestionType type)
{
    Question *newQuestion = (Question *)malloc(sizeof(Question));
    strcpy(newQuestion->question, question);
    newQuestion->type = type;

    newQuestion->prev = NULL;
    newQuestion->next = NULL;

    newQuestion->asked = false;

    if (firstQuestion == NULL)
    {
        newQuestion->id = 1;
        firstQuestion = newQuestion;
        lastQuestion = newQuestion;
    }
    else
    {
        newQuestion->id = lastQuestion->id + 1;
        lastQuestion->next = newQuestion;
        newQuestion->prev = lastQuestion;
        lastQuestion = newQuestion;
    }

    return newQuestion;
}

void saveQuestionToFile(Question *question)
{
    FILE *file = fopen("storage/questions.bin", "ab");

    if (file == NULL)
    {
        fclose(file);
        return;
    }

    fwrite(question, sizeof(*question), 1, file);

    fclose(file);
}

void refreshQuestionsFile()
{
    FILE *file = fopen("storage/questions.bin", "wb");

    if (file == NULL)
    {
        fclose(file);
        return;
    }

    Question *current = firstQuestion;

    while (current != NULL)
    {
        fwrite(current, sizeof(*current), 1, file);
        current = current->next;
    }

    fclose(file);
}

void newQuestion()
{
    Screen.clear();

    if (Screen.getOS() == 'U')
    {
        char tempC;
        scanf("%c", &tempC);
    }

    char question[100];
    fflush(stdin);
    printf(COLOR_Blue "\n> Qual é a pergunta? " COLOR_Default);
    fgets(question, sizeof(question), stdin);
    question[strcspn(question, "\n")] = '\0';

    int type;
    printf(COLOR_Blue "\n> Qual é o tipo da pergunta (0 - Escolha multipla, 1 - Verdadeiro/Falso, 2 - Resposta direta)? " COLOR_Default);
    scanf("%d", &type);
    getchar();

    Question *newQ = createQuestion(question, (QuestionType)type);

    Screen.clear();
    if (newQ->type == MULTIPLE_CHOICE)
    {
        printf(COLOR_Yellow "\nInsira agora as respostas à questão. \n\n" COLOR_Default);
        for (int i = 0; i < 4; i++)
        {
            char option[100];
            fflush(stdin);
            printf(COLOR_Blue "\n> Resposta #%d: " COLOR_Default, i + 1);
            fgets(option, sizeof(option), stdin);
            option[strcspn(option, "\n")] = '\0';
            strcpy(newQ->options[i], option);
        }
        char answer[100];
        fflush(stdin);
        printf(COLOR_Blue "\n> Resposta (1-4): " COLOR_Default);
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';
        strcpy(newQ->answer, answer);
    }
    else if (newQ->type == TRUE_FALSE || newQ->type == DIRECT_RESPONSE)
    {
        char answer[100];
        fflush(stdin);
        printf(COLOR_Blue "\n> Resposta: " COLOR_Default);
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';
        strcpy(newQ->answer, answer);
    }

    saveQuestionToFile(newQ);
}

void loadQuestions()
{
    FILE *file = fopen("storage/questions.bin", "rb");

    if (file == NULL)
    {
        FILE *createFile = fopen("storage/questions.bin", "wb");
        fclose(createFile);
        fclose(file);
        return;
    }

    Question temp;
    while (fread(&temp, sizeof(Question), 1, file) == 1)
    {
        Question *newQuestion = createQuestion(temp.question, temp.type);
        memcpy(newQuestion->options, temp.options, sizeof(temp.options));
        strcpy(newQuestion->answer, temp.answer);
        newQuestion->asked = temp.asked;
    }

    fclose(file);
}

void listQuestions()
{
    Screen.clear();

    if (firstQuestion == NULL)
    {
        Exceptions.setError("A lista de questões está vazia. Por favor, crie uma questão primeiro!");
        Exceptions.printError();
        Screen.awaitInteraction();
        return;
    }

    Question *temp = firstQuestion;

    printf(COLOR_Blue "---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("    ID        \t\t\tQuestão        \t\t\t\tTipo        \t\t\tResposta(s)            \n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n" COLOR_Default);

    while (temp != NULL)
    {
        char type[50];

        switch (temp->type)
        {
        case 0:
            strcpy(type, "Escolha múltipla");
            break;

        case 1:
            strcpy(type, "Verdadeiro ou Falso");
            break;

        case 2:
            strcpy(type, "Resposta direta");
            break;
        }

        printf("\n    %-8d\t\t\t%-32s\t\t%-19s%-13s", temp->id, Functions.truncate(temp->question, 32), type, "");

        if (temp->type == MULTIPLE_CHOICE)
        {
            for (int i = 0; i < 4; i++)
            {
                if (i != 0)
                {
                    char chTemp[5];
                    Functions.toString(chTemp, i + 1);
                    if (strcmp(chTemp, temp->answer) == 0)
                        printf("%-112s" COLOR_Cyan "%d)" COLOR_Green " %s\n", "", i + 1, temp->options[i]);
                    else
                        printf("%-112s" COLOR_Cyan "%d)" COLOR_Default " %s\n", "", i + 1, temp->options[i]);
                }
                else
                {
                    char chTemp[5];
                    Functions.toString(chTemp, i + 1);
                    if (strcmp(chTemp, temp->answer) == 0)
                        printf(COLOR_Cyan "%d)" COLOR_Green " %s\n", i + 1, temp->options[i]);
                    else
                        printf(COLOR_Cyan "%d)" COLOR_Default " %s\n", i + 1, temp->options[i]);
                }
            }
        }
        else if (temp->type == TRUE_FALSE || temp->type == DIRECT_RESPONSE)
        {
            if (strcmp(temp->answer, "Verdadeiro") == 0)
                printf(COLOR_Green);
            else if (strcmp(temp->answer, "Falso") == 0)
                printf(COLOR_Red);
            else
                printf(COLOR_Cyan);

            printf("%s\n" COLOR_Default, temp->answer);
        }

        printf(COLOR_Blue "\n---------------------------------------------------------------------------------------------------------------------------------------------------------\n" COLOR_Default);

        temp = temp->next;
    }

    Screen.awaitInteraction();
}

void removeQuestion()
{
    Screen.clear();

    if (Screen.getOS() == 'U')
    {
        char tempC;
        scanf("%c", &tempC);
    }

    if (firstQuestion == NULL)
    {
        Screen.clear();
        Exceptions.setError("Nenhuma questão foi criada. É necessário criar uma questão antes de poder removê-la.");
        Exceptions.printError();
        Screen.awaitInteraction();
        return;
    }

    int id;

    do
    {
        if (error)
        {
            Screen.clear();
            Exceptions.printError();
        }

        fflush(stdin);
        printf(COLOR_Blue "> Número da questão a remover: " COLOR_Default);
        scanf("%d", &id);

        if (!questionExists(id))
            Exceptions.setError("Essa questão não existe!");
    } while (error);

    Question *current = firstQuestion;

    while (current != NULL)
    {
        if (current->id == id)
            break;

        current = current->next;
    }

    Screen.awaitInteraction();

    if (current->prev == NULL)
    {
        firstQuestion = current->next;

        if (firstQuestion != NULL)
            firstQuestion->prev = NULL;
    }
    else
    {
        // The question to be removed is not the first question in the list
        current->prev->next = current->next;

        if (current->next != NULL)
            current->next->prev = current->prev;
    }

    free(current);

    refreshQuestionsFile();
}

void freeQuestions()
{
    while (firstQuestion != NULL)
    {
        Question *current = firstQuestion;
        firstQuestion = firstQuestion->next;
        free(current);
    }
}

/**
 *
 *
 * Game-related functions
 *
 *
 */
Question *getRandomQuestion()
{
    int count = 0;
    Question *temp = firstQuestion;
    while (temp != NULL)
    {
        if (temp->asked == false)
        {
            count++;
        }
        temp = temp->next;
    }

    if (count == 0)
    {
        temp = firstQuestion;
        while (temp != NULL)
        {
            temp->asked = false;
            temp = temp->next;
        }
    }

    int randomIndex = rand() % count;

    temp = firstQuestion;
    while (temp != NULL)
    {
        if (temp->asked == false)
        {
            if (randomIndex == 0)
            {
                return temp;
            }
            randomIndex--;
        }
        temp = temp->next;
    }

    return NULL;
}

bool askQuestion()
{
    if (firstQuestion == NULL)
        return false;

    Question *question = getRandomQuestion();

    char tip[22];

    if (question->type == DIRECT_RESPONSE)
        strcpy(tip, "(Resposta direta)");
    else if (question->type == TRUE_FALSE)
        strcpy(tip, "(Verdadeiro ou Falso)");
    else
        strcpy(tip, "");

    printf(COLOR_Green "> " COLOR_Blue "%s? " COLOR_Green "%s\n" COLOR_Default, question->question, tip);

    if (question->type == MULTIPLE_CHOICE)
        for (int i = 0; i < 4; i++)
            printf(COLOR_Cyan "%d)" COLOR_Default " %s\n", i + 1, question->options[i]);

    printf(COLOR_Blue "\n> Resposta? \n- " COLOR_Default);

    char answer[50];
    int userAnswer, correctAnswer;
    fgets(answer, sizeof(answer), stdin);
    answer[strcspn(answer, "\n")] = '\0';

    if (strcmp(answer, question->answer) == 0)
    {
        printf(COLOR_Green "\nParabéns, acertaste a questão! Vais andar 1 casa para a frente!\n\n" COLOR_Default);
        Screen.awaitInteraction();
        return true;
    }
    else
    {
        printf(COLOR_Red "\nOhhh :(, parece que erraste a questão! Vais recuar uma casa!\n\n" COLOR_Default);
        Screen.awaitInteraction();
        return false;
    }

    return false;
}