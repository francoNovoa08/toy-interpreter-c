#include "token.h"
#include "utils/token_utils.h"
#include <stdlib.h>
#include <string.h>

Token *tokenise_string(char *string, size_t *tokens) {
  remove_all_whitespace(string);
  size_t len = strlen(string);
  Token *token_array = malloc(len * sizeof(Token));
  size_t token_count = 0;
  size_t i = 0;

  while (i < len) {
    Token token;
    switch (string[i]) {
    case '+':
      token.type = TOKEN_PLUS;
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case '-':
      token.type = TOKEN_MINUS;
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case '*':
      token.type = TOKEN_TIMES;
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case '/':
      token.type = TOKEN_OVER;
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    default:
      token.type = TOKEN_NUMBER;
    }

    size_t next = i + 1;
    size_t counter = 1;
    size_t num = string[i] - '0';
    while (next < len && string[next] != '+' && string[next] != '-' && string[next] != '*' &&
           string[next] != '/') {
      num *= 10;
      num += string[next] - '0';
      counter++;
      next++;
    }

    token.value = num;
    token_array[token_count] = token;
    token_count++;
    i += counter;
  }

  *tokens = token_count;
  return token_array;
}