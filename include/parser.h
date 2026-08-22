#ifndef PARSER_H
#define PARSER_H

#include "utils/AST.h"
#include "token.h"

typedef struct {
  Token *tokens;
  size_t token_count;
  size_t pos;
  char *error_message;
} ParserState;

/**
 * @brief Parses a sequence of one or more operands combined by + or -,
 *      building nested nodes left to right.
 *
 * @param state The shared state passed in.
 *
 * @return The built subtree.
 */
AST_Node *parse_additive(ParserState *state);

/**
 * @brief Parses a sequence of one or more operands combined by * or /,
 *      building nested nodes left to right.
 *
 *
 * @param state The shared state passed in.
 *
 * @return The built subtree.
 */
AST_Node *parse_multiplicative(ParserState *state);

#endif // PARSER_H