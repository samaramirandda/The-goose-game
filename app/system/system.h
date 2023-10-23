typedef struct System {
    /**
     * 
     * @name Boot up the system
     * @brief This function is called whenever we start the program
     * @author João Ferreira and Samara Miranda
    */
    void (*boot)();
} SystemController;

#include "system.c"