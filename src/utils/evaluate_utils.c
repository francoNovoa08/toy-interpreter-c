#include "utils/evaluate_utils.h"
#include <stdlib.h>
#include <string.h>

char* get_variable_name(const char *start, size_t length) {
    char *new_str = (char*)malloc((length + 1) * sizeof(char));

    if (new_str == NULL) {
        return NULL;
    }

    memcpy(new_str, start, length);
    new_str[length] = '\0';

    return new_str;
}