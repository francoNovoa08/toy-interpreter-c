#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>
typedef enum {
  TOKEN_NUMBER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_TIMES,
  TOKEN_OVER,
  TOKEN_LEFT_BRACKET,
  TOKEN_RIGHT_BRACKET,
  TOKEN_IDENTIFIER,
  TOKEN_ASSIGNMENT,
  TOKEN_GREATER_THAN,
  TOKEN_LESS_THAN,
  TOKEN_EQUALS,
  TOKEN_GREATER_THAN_OR_EQUAL,
  TOKEN_LESS_THAN_OR_EQUAL,
  TOKEN_NOT_EQUAL,
  TOKEN_IF,
  TOKEN_CURLY_LEFT_BRACKET,
  TOKEN_CURLY_RIGHT_BRACKET,
  TOKEN_WHILE,
} TokenType;

typedef struct {
  union {
    int number_value;
    struct {
      const char *start;
      size_t length;
    } identifier;
  } value;
  TokenType type;
} Token;

/**
 * @brief Converts a string into Token types.
 *
 * @param string The string to tokenise
 * @param tokens The number of tokens to be modified in place by the function
 * @return A pointer to a dynamically-allocated Token type array
 */
Token *tokenise_string(char *string, size_t *tokens);

#endif // TOKEN_H