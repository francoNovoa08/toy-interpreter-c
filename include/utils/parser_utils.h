#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "parser.h"
#include "utils/data_structures/AST.h"

/**
 * @brief Parses a conditional statement and its block (includes loops)
 *
 * @param state The shared state passed in
 *
 * @return The built subtree for the conditional.
 */
AST_Node *parse_conditional_block(ParserState *state);

#endif // PARSER_UTILS_H