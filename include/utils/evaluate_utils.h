#ifndef EVALUATE_UTILS_H
#define EVALUATE_UTILS_H

#include <stddef.h>

/**
 * @brief Gets the name of a variable from a starting pointer and length
 *
 * @param start The pointer to the first character in the name
 * @param length The number of characters in the name
 *
 * @return The variable name as a string
 */
char* get_variable_name(const char *start, size_t length);

#endif // EVALUATE_UTILS_H