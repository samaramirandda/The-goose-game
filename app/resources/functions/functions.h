typedef struct Functions
{
    char *(*truncate)(char *str, int chars);
    void (*getCurrentDate)(char* buffer, size_t bufferSize);
    void (*getCurrentTime)(int* hour, int* minute);
    int (*compareDates)(char *date1, char *date2);
    void (*toString)(char str[], int num);
    int (*toInt)(char str[]);
} FunctionsController;

#include "functions.c"