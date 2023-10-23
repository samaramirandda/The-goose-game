// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

// Autoload
#include "app/autoload.h"

void main()
{
  // Boot up game
  System.boot();
  Questions.loadQuestions();

  // Open the main menu
  mainMenu();

  // CLear memory
  Questions.freeQuestions();
  Users.freeUsers();
}
