/*
 *
 * @name Boot
 * @brief This function boots up the program with a serie of commands
 * @author João Ferreira and Samara Miranda
 *
 * */
void boot()
{
  Users.importUsersFromFile();
  setlocale(LC_ALL, "Portuguese");
}