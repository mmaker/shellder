/**
 * \mainpage Welcome to the shellder documentation!
 *
 * Here you can find all specific informations about the shell, how each
 * internal structure is defined, and in which way which functions interacts
 * with them.
 */

#ifndef __SHELL_H__
#define __SHELL_H__
/**
 * \file shell.h
 * \brief View functions.
 *
 * \detail This file exports the main functions used to nteract with the user.
 */


extern char* PS1;


/**
 * \brief Main loop for the shell.
 *
 * \param slogfile The string for the logfile. External varialbe logfile will
 *                  be updated accordingly
 *
 */
void main_shellder();

#endif
