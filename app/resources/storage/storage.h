typedef struct Storage {
    int (*lines)(char fileName[]);
    void (*createFile)(char fileName[]);
    bool (*isEmptyFile)(char fileName[]);
    void (*appendFile)(char fileName[], char text[]);
    void (*writeFile)(char fileName[], char text[]);
    void (*removeFile)(char fileName[]);
    void (*clearFile)(char fileName[]);
    void (*renameFile)(char fileName[], char newFileName[]);
    void (*copyFile)(char fileName[], char newFileName[]);
} StorageController;

#include "storage.c"