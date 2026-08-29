#ifndef TOKEN_UTILS_H
#define TOKEN_UTILS_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Removes all whitespace in place from a string
 *
 * @pre @p string must be a char[], not a string literal
 *
 * @param string The string to remove whitespace from
 */
void remove_all_whitespace(char *string);

/**
 * @brief Checks if some tokenised string is an "if" keyword
 *
 * @param start The pointer to the start of the string
 * @param length The number of characters in the string
 * 
 * @return True if the string is an "if" keyword
 */
bool is_if_keyword(const char *start, size_t length);

/**
 * @brief Checks if some tokenised string is a "while" keyword
 *
 * @param start The pointer to the start of the string
 * @param length The number of characters in the string
 * 
 * @return True if the string is a "while" keyword
 */
bool is_while_keyword(const char *start, size_t length);

#endif // TOKEN_UTILS_H