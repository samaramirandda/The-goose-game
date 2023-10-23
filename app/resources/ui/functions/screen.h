typedef struct Screen {
    /**
     * 
     * @name Clear screen
     * @brief This function is called whenever we want to clear the screen
     * @author João Ferreira and Samara Miranda
     * 
    */
    void (*clear)();

    /**
     * 
     * @name Create title
     * @brief This function is called whenever we want to create a menu title
     * @author João Ferreira and Samara Miranda
     * 
    */
    void (*title)(char title[]);

    /**
     * 
     * @name Create menu
     * @brief This function is called whenever we want to create a screen menu with options
     * @author João Ferreira and Samara Miranda
     * 
    */
    void (*menu)(char *options[], int quantity, bool prompt);

    /**
     * 
     * @name Get operating system
     * @brief This function is called whenever we want to get the user operating system
     * @author João Ferreira and Samara Miranda
     * 
    */
    char (*getOS)();

    /**
     * 
     * @name Wait for user interaction
     * @brief This function is called whenever we want to wait for the user to interact with the program
     * @author João Ferreira and Samara Miranda
     * 
    */
    void (*awaitInteraction)();
} ScreenController;

#include "screen.c"