#ifndef ERRORS
#define ERRORS
    // Define the variables
    #define MAX_ERROR_LENGTH 150
    bool error = false;
    char errorMessage[MAX_ERROR_LENGTH] = { '\0' };

    typedef struct Exceptions {
        void (*setError)(const char* message);
        void (*printError)();
    } ExceptionsController;

    // Include all functions
    #include "errors.c"
#endif // !ERRORS
