/**
 * \file shell.h
 * \brief View functions.
 *
 * This file exports the main functions used to nteract with the user.
 */


char** environ;
char* PS1 = ">>> ";


/**
 * \brief Main loop for the shell.
 *
 * \param slogfile The string for the logfile. External varialbe logfile will
 *                  be updated accordingly
 *
 */
void main_shellder();


