/**
 * \file utils.h
 * \brief Various string/array utilities.
 *
 *
 */


/**
 * \brief Removes trailing and leading whitespaces from a string.
 * \param s the string to be stripped,
 * \param n pointer to the current length of the string, that will be updated.
 *
 */
void strip(char** s, size_t* n);


/**
 * \brief Splits a string on each whitespace, taking into account quotes.
 *
 * TODO: to be implemented accordingly to double and single quotes, with escape
 * sequences etc.
 */
char* split(char* s);

