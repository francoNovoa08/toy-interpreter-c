#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#define VECTOR_INIT_CAPACITY 4

typedef struct {
    char **items;
    size_t capacity;
    size_t size;
} Vector;

/**
 * @brief Creates a Vector
 *
 * @param vec An empty vector type
 *
 * @return True if successful, else false
 */
bool Vector_init(Vector *vec);

/**
 * @brief Inserts an element to the last position in the vector
 *
 * @param vec The Vector
 * @param str The string to insert
 *
 * @return True if successful, else false
 */
bool Vector_push(Vector *vec, const char *str);

/**
 * @brief Gets an element from a vector's index
 *
 * @param vec The Vector
 * @param index The index to return from
 *
 * @return The string at that index.
 */
const char *Vector_get(const Vector *vec, size_t index);

/**
 * @brief Inserts an element at a specified index
 *
 * @param vec The Vector to insert into.
 * @param str The string to insert.
 *
 * @return True if successful, else false
 */
bool Vector_set(Vector *vec, size_t index, const char *str);

/**
 * @brief Searches for the presence of a string in the Vector
 *
 * @param vec The Vector to search.
 * @param str The string to search for.
 *
 * @return True if found, else false
 */
bool Vector_search(Vector *vec, const char *str);

/**
 * @brief Removes the element at the last position in the Vector
 *
 * @param vec The Vector
 */
void Vector_pop(Vector *vec);

/**
 * @brief Frees a vector.
 *
 * @param vec The Vector
 */
void Vector_free(Vector *vec);

#endif // VECTOR_H