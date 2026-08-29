#include "utils/token_utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void remove_all_whitespace(char *string) {
  if (string == NULL) {
    return;
  }

  char *read_ptr = string;
  char *write_ptr = string;

  while (*read_ptr != '\0') {
    if (!isspace((unsigned char)*read_ptr)) {
      *write_ptr = *read_ptr;
      write_ptr++;
    }
    read_ptr++;
  }
  *write_ptr = '\0';
}

bool is_if_keyword(const char* start, size_t length) {
  return (length == 2) && (strncmp(start, "if", 2) == 0);
}