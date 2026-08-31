#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/data_structures/vector.h"


static char *safe_strdup(const char *src) {
    if (!src) return NULL;
    size_t len = strlen(src) + 1;
    char *dest = malloc(len);
    if (dest) {
        memcpy(dest, src, len);
    }
    return dest;
}

bool Vector_init(Vector *vec) {
    if (!vec) return false;
    
    vec->capacity = VECTOR_INIT_CAPACITY;
    vec->size = 0;
    vec->items = malloc(sizeof(char *) * vec->capacity);
    
    return vec->items != NULL;
}

static bool Vector_resize(Vector *vec, size_t new_capacity) {
    if (!vec || new_capacity == 0) return false;

    char **new_items = realloc(vec->items, sizeof(char *) * new_capacity);
    if (!new_items) {
        return false;
    }

    vec->items = new_items;
    vec->capacity = new_capacity;
    return true;
}

bool Vector_push(Vector *vec, const char *str) {
    if (!vec) return false;

    if (vec->size == vec->capacity) {
        if (vec->capacity > (size_t)-1 / 2) return false; 
        
        if (!Vector_resize(vec, vec->capacity * 2)) {
            return false;
        }
    }

    char *copy = safe_strdup(str);
    if (str && !copy) {
        return false;
    }

    vec->items[vec->size++] = copy;
    return true;
}

const char *Vector_get(const Vector *vec, size_t index) {
    if (!vec || index >= vec->size) {
        return NULL;
    }
    return vec->items[index];
}

bool Vector_set(Vector *vec, size_t index, const char *str) {
    if (!vec || index >= vec->size) {
        return false;
    }

    char *copy = safe_strdup(str);
    if (str && !copy) {
        return false;
    }

    free(vec->items[index]); 
    vec->items[index] = copy;
    return true;
}

bool Vector_search(Vector *vec, const char *str) {
    for (size_t i = 0; i < vec->capacity; i++) {
        if (strcmp(str, Vector_get(vec, i)) == 0) {
            return true;
        }
    }
    return false;
}

void Vector_pop(Vector *vec) {
    if (!vec || vec->size == 0) {
        return;
    }
    
    vec->size--;
    free(vec->items[vec->size]);
    vec->items[vec->size] = NULL; 
    
    if (vec->size > 0 && vec->size == vec->capacity / 4) {
        size_t new_capacity = vec->capacity / 2;
        if (new_capacity >= VECTOR_INIT_CAPACITY) {
            Vector_resize(vec, new_capacity);
        }
    }
}

void Vector_free(Vector *vec) {
    if (!vec || !vec->items) return;

    for (size_t i = 0; i < vec->size; i++) {
        free(vec->items[i]);
    }
    
    free(vec->items);
    vec->items = NULL;
    vec->capacity = 0;
    vec->size = 0;
}