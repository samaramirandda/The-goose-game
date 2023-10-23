/*
 *
 * @name Set error message
 * @brief This function sets an error message
 * @author João Ferreira and Samara Miranda
 *
 * */
void setError(const char *message)
{
    error = true;
    strcpy(errorMessage, COLOR_Red);
    strcat(errorMessage, message);
}

/*
 *
 * @name Print message
 * @brief This function prints the error message
 * @author João Ferreira and Samara Miranda
 *
 * */
void printError()
{
    printf(COLOR_Red"         - ERRO ENCONTRADO -\n");
    printf("%s\n", errorMessage);
    error = false;
    errorMessage[0] = '\0';
}