#ifndef PARSER_H
#define PARSER_H

#include "utils/data_structures/AST.h"
#include "token.h"
#include "utils/errors.h"

typedef struct {
  Token *tokens;
  size_t token_count;
  size_t pos;
  ErrorCode error;
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

/**
 * @brief Parses a single unit, either a number or parenthesised expression
 *
 *
 * @param state The shared state passed in.
 *
 * @return The built subtree.
 */
AST_Node *parse_primary(ParserState *state);

#endif // PARSER_H