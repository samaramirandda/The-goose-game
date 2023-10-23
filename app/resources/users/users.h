#define MAXUSERS 100

typedef struct User
{
    char username[50], password[50], name[50], nationality[50], lastPlayingDate[20];
    bool isAdmin, loggedIn;
    int age, id;
    struct User *prev;
    struct User *next;
} User;

typedef struct Users
{
    bool (*userExists)(char username[]);
    bool (*isUserAdmin)(char username[]);
    bool (*isLoggedIn)(User *user);
    User *(*getUserByUsername)(char username[]);
    void (*insertUserAtEnd)(User *user);
    void (*saveUserToFile)(User *user);
    void (*importUsersFromFile)();
    void (*refreshUsersFile)();
    void (*createUser)(char username[], char password[], char name[], int age, char nationality[], char lastPlayingDate[], bool isAdmin);
    void (*registerUser)();
    void (*removeUser)();
    bool (*checkLogin)(char username[], char password[]);
    User *(*login)();
    void (*adminLogin)();
    User *(*logout)(User *user);
    void (*adminLogout)();
    int (*compareUsersByUsername)(User *user1, User *user2);
    void (*insertionSortUsersByUsername)();
    void (*insertionSortUsersByAge)();
    void (*displayUsers)();
    void (*displayPlayers)();
    void (*updatePlayingDate)(User *players[4], int playerAmount);
    void (*freeUsers)();
} UsersController;

// List and admin user
User *firstUser = NULL, *adminUser = NULL;

// Players
User *firstPlayer = NULL, *secondPlayer = NULL, *thirdPlayer = NULL, *fourthPlayer = NULL;

#include "users.c"