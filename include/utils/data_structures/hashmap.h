#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdbool.h>
#define INITIAL_CAPACITY 8
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    size_t capacity;
    size_t size;
} HashMap;

/**
 * @brief Hashing function for the HashMap
 *
 * @param key A pointer to the key to the hash
 * @param capacity The current capacity of the HashMap
 *
 * @return The hashed key
 */
static unsigned int hash_function(const char *key, size_t capacity);

/**
 * @brief Creates a HashMap
 *
 * @return A pointer to the created HashMap
 */
HashMap* HashMap_create();

/**
 * @brief Resizes the HashMap
 *
 * @param map The Hashmap
 *
 * @return True on success, else false
 */
static bool HashMap_resize(HashMap *map);

/**
 * @brief Inserts a key and value into the HashMap
 *
 * @param map The HashMap
 * @param key The key to insert
 * @param value The value to be inserted
 *
 * @return True on success, else false
 */
bool HashMap_insert(HashMap *map, const char *key, int value);

/**
 * @brief Gets a value at a key in the HashMap
 *
 * @param map The HashMap
 * @param key The key from which to retrieve the value
 * @param out_value A variable to be modified to the retrieved value
 *
 * @return True on success, else false
 */
bool HashMap_get(HashMap *map, const char *key, int *out_value);

/**
 * @brief Deletes a key (and its value) from the HashMap
 *
 * @param map The HashMap
 * @param key The key to be deleted
 *
 * @return True on success, else false
 */
bool HashMap_delete(HashMap *map, const char *key);

/**
 * @brief Frees the memory allocated for a HashMap
 *
 * @param map The HashMap
 */
void HashMap_free(HashMap *map);

#endif // HASHMAP_H