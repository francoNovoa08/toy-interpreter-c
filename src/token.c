#include "token.h"
#include "utils/token_utils.h"
#include <ctype.h>
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
    case '(':
      token.type = TOKEN_LEFT_BRACKET;
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case ')':
      token.type = TOKEN_RIGHT_BRACKET;
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case '=':
      if (i == len || string[i + 1] != '=') {
        token.type = TOKEN_ASSIGNMENT;
      } else {
        token.type = TOKEN_EQUALS;
        i++;
      }

      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case '<':
      if (i == len || string[i + 1] != '=') {
        token.type = TOKEN_LESS_THAN;
      } else {
        token.type = TOKEN_LESS_THAN_OR_EQUAL;
        i++;
      }
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case '>':
      if (i + 1 == len || string[i + 1] != '=') {
        token.type = TOKEN_GREATER_THAN;
      } else {
        token.type = TOKEN_GREATER_THAN_OR_EQUAL;
        i++;
      }

      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case '!':
      token.type = TOKEN_NOT_EQUAL;
      token_array[token_count] = token;
      token_count++;
      i += 2;
      continue;
    case '{':
      token.type = TOKEN_CURLY_LEFT_BRACKET;
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    case '}':
      token.type = TOKEN_CURLY_RIGHT_BRACKET;
      token_array[token_count] = token;
      token_count++;
      i++;
      continue;
    }

    size_t next = i + 1;
    size_t counter = 1;

    if (isdigit((unsigned char)string[i])) {
      token.type = TOKEN_NUMBER;
      size_t num = string[i] - '0';
      while (next < len && isdigit((unsigned char)string[next])) {
        num *= 10;
        num += string[next] - '0';
        counter++;
        next++;
      }

      token.value.number_value = num;
      token_array[token_count] = token;
      token_count++;
      i += counter;
      continue;
    }

    while (next < len && (isalnum(string[next]) || string[next] == '_')) {
      counter++;
      next++;
    }

    if (is_if_keyword(&string[i], counter)) {
      token.type = TOKEN_IF;
    } else if (is_while_keyword(&string[i], counter)) {
      token.type = TOKEN_WHILE;
    } else {
      token.type = TOKEN_IDENTIFIER;
      token.value.identifier.start = &string[i];
      token.value.identifier.length = counter;
    }

    token_array[token_count] = token;
    token_count++;
    i += counter;
  }

  *tokens = token_count;
  return token_array;
}