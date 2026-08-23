#include "parser.h"
#include "utils/AST.h"
#include <stdlib.h>

AST_Node *parse_additive(ParserState *state) {
  Token *tokens = state->tokens;

  AST_Node *tree = parse_multiplicative(state);
  Token current_token = tokens[state->pos];
  if (tree == NULL) {
    state->error = PARSE_ERR_SUBEXPRESSION_FAILED;
    return NULL;
  }

  while (
      state->pos < state->token_count - 1 &&
      (current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS)) {
    AST_Node *consumed_token_node = AST_build_node_from_token(current_token);
    if (consumed_token_node == NULL) {
      state->error = PARSE_ERR_MEMORY_ALLOCATION;
      return NULL;
    }

    state->pos++;
    consumed_token_node->left = tree;

    if (state->pos < state->token_count) {
      current_token = tokens[state->pos];
      if (current_token.type != TOKEN_NUMBER) {
        state->error = PARSE_ERR_EXPECTED_NUMBER;
        return NULL;
      }
      AST_Node *new_node = parse_multiplicative(state);
      current_token = tokens[state->pos];
      if (new_node == NULL) {
        state->error = PARSE_ERR_SUBEXPRESSION_FAILED;
        return NULL;
      }

      consumed_token_node->right = new_node;
    }
    tree = consumed_token_node;
  }

  return tree;
}

AST_Node *parse_multiplicative(ParserState *state) {
  Token *tokens = state->tokens;
  Token current_token = tokens[state->pos];
  if (current_token.type != TOKEN_NUMBER) {
    state->error = PARSE_ERR_EXPECTED_NUMBER;
    return NULL;
  }

  AST_Node *tree = AST_build_node_from_token(current_token);
  if (tree == NULL) {
    state->error = PARSE_ERR_MEMORY_ALLOCATION;
    return NULL;
  }

  state->pos++;
  if (state->pos == state->token_count) {
    return tree;
  }
  current_token = tokens[state->pos];

  if (current_token.type == TOKEN_NUMBER) {
    state->error = PARSE_ERR_EXPECTED_OPERATOR;
    return NULL;
  }

  while (
      state->pos < state->token_count - 1 &&
      (current_token.type == TOKEN_TIMES || current_token.type == TOKEN_OVER)) {
    AST_Node *consumed_token_node = AST_build_node_from_token(current_token);
    if (consumed_token_node == NULL) {
      state->error = PARSE_ERR_MEMORY_ALLOCATION;
      return NULL;
    }

    state->pos++;
    consumed_token_node->left = tree;

    if (state->pos < state->token_count) {
      current_token = tokens[state->pos];
      if (current_token.type != TOKEN_NUMBER) {
        state->error = PARSE_ERR_EXPECTED_NUMBER;
        return NULL;
      }
      AST_Node *new_node = AST_build_node_from_token(current_token);
      if (new_node == NULL) {
        state->error = PARSE_ERR_MEMORY_ALLOCATION;
        return NULL;
      }

      state->pos++;
      if (state->pos < state->token_count) {
        current_token = tokens[state->pos];
      }

      consumed_token_node->right = new_node;
    }
    tree = consumed_token_node;
  }

  return tree;
}