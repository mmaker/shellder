/**
 * \file shell.h
 * \brief View functions.
 *
 * This file exports the main functions used to nteract with the user.
 */


FILE* logfile = NULL;
char** environ;
const char* PS1 = ">>> ";


/**
 * \brief Prints out an help for each command line argument, then exit.
 *
 */
void print_help(char* exe, int returncode);


/**
 * \brief Main loop for the shell.
 *
 * \param slogfile The string for the logfile. External varialbe logfile will
 *                  be updated accordingly
 *
 */
void main_shellder(char* slogfile);


