#define _GNU_SOURCE
#include "utils/data_structures/hashmap.h"
#include <stdlib.h>
#include <string.h>

static unsigned int hash_function(const char *key, size_t capacity) {
  unsigned int hash = 2166136261u;
  while (*key) {
    hash ^= (unsigned char)*key++;
    hash *= 16777619u;
  }
  return hash % capacity;
}

HashMap *HashMap_create() {
  HashMap *map = malloc(sizeof(HashMap));
  if (!map)
    return NULL;

  map->capacity = INITIAL_CAPACITY;
  map->size = 0;
  map->buckets = calloc(map->capacity, sizeof(HashNode *));

  if (!map->buckets) {
    free(map);
    return NULL;
  }
  return map;
}

static bool HashMap_resize(HashMap *map) {
  size_t old_capacity = map->capacity;
  size_t new_capacity = old_capacity * 2;

  HashNode **new_buckets = calloc(new_capacity, sizeof(HashNode *));
  if (!new_buckets)
    return false;

  for (size_t i = 0; i < old_capacity; i++) {
    HashNode *current = map->buckets[i];
    while (current != NULL) {
      HashNode *next = current->next;
      unsigned int new_index = hash_function(current->key, new_capacity);

      current->next = new_buckets[new_index];
      new_buckets[new_index] = current;

      current = next;
    }
  }

  free(map->buckets);
  map->buckets = new_buckets;
  map->capacity = new_capacity;
  return true;
}

bool HashMap_insert(HashMap *map, const char *key, int value) {
  if (!map || !key)
    return false;

  if ((float)(map->size + 1) / map->capacity > LOAD_FACTOR_THRESHOLD) {
    if (!HashMap_resize(map)) {
      return false;
    }
  }

  unsigned int index = hash_function(key, map->capacity);
  HashNode *current = map->buckets[index];

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      current->value = value;
      return true;
    }
    current = current->next;
  }

  HashNode *new_node = malloc(sizeof(HashNode));
  if (!new_node)
    return false;

  new_node->key = strdup(key);
  if (!new_node->key) {
    free(new_node);
    return false;
  }
  new_node->value = value;

  new_node->next = map->buckets[index];
  map->buckets[index] = new_node;
  map->size++;

  return true;
}

bool HashMap_get(HashMap *map, const char *key, int *out_value) {
  if (!map || !key || !out_value)
    return false;

  unsigned int index = hash_function(key, map->capacity);
  HashNode *current = map->buckets[index];

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      *out_value = current->value;
      return true;
    }

    current = current->next;
  }
  return false;
}

bool HashMap_delete(HashMap *map, const char *key) {
  if (!map || !key)
    return false;

  unsigned int index = hash_function(key, map->capacity);
  HashNode *current = map->buckets[index];
  HashNode *prev = NULL;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      if (prev == NULL) {
        map->buckets[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current->key);
      free(current);
      map->size--;
      return true;
    }
    prev = current;
    current = current->next;
  }
  return false;
}

void HashMap_free(HashMap *map) {
  if (!map)
    return;

  for (size_t i = 0; i < map->capacity; i++) {
    HashNode *current = map->buckets[i];
    while (current != NULL) {
      HashNode *next = current->next;
      free(current->key);
      free(current);
      current = next;
    }
  }
  free(map->buckets);
  free(map);
}