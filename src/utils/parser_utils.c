#include "utils/parser_utils.h"
#include <stdlib.h>

AST_Node *parse_conditional_block(ParserState *state) {
  Token *tokens = state->tokens;
  AST_Node *conditional_node = AST_build_node_from_token(tokens[state->pos]);
  state->pos++;
  if (state->pos == state->token_count ||
      tokens[state->pos].type != TOKEN_LEFT_BRACKET) {
    state->error = PARSE_ERR_MISSING_BRACE;
    return NULL;
  }

  state->pos++;
  AST_Node *comparison = parse_comparison(state);
  if (comparison == NULL) {
    return NULL;
  }
  conditional_node->left = comparison;

  Token current_token = tokens[state->pos];
  if (current_token.type != TOKEN_RIGHT_BRACKET) {
    state->error = PARSE_ERR_MISSING_BRACE;
    return NULL;
  }

  state->pos++;
  current_token = tokens[state->pos];
  if (current_token.type != TOKEN_CURLY_LEFT_BRACKET) {
    state->error = PARSE_ERR_MISSING_CURLY_BRACE;
    return NULL;
  }

  state->pos++;
  current_token = tokens[state->pos];

  AST_Node *head = malloc(sizeof(AST_Node));
  head->type = NODE_STATEMENT_LIST;
  AST_Node *current_node = head;
  while (current_token.type != TOKEN_CURLY_RIGHT_BRACKET &&
         state->pos < state->token_count) {
    AST_Node *left = parse_statement(state);
    current_node->left = left;
    current_token = tokens[state->pos];
    if (left == NULL) {
      return NULL;
    }

    if (current_token.type != TOKEN_CURLY_RIGHT_BRACKET) {
      AST_Node *right = malloc(sizeof(AST_Node));
      if (right == NULL) {
        state->error = PARSE_ERR_MEMORY_ALLOCATION;
        return NULL;
      }
      current_node->right = right;
      current_node = current_node->right;
    }

    current_node->right = NULL;
    current_node->type = NODE_STATEMENT_LIST;
  }
  state->pos++;
  conditional_node->right = head;

  return conditional_node;
}