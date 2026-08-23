#include "parser.h"
#include "utils/AST.h"
#include <stdlib.h>

AST_Node *parse_additive(ParserState *state) {
  Token *tokens = state->tokens;

  AST_Node *tree = parse_multiplicative(state);
  if (tree == NULL) {
    return NULL;
  }

  if (state->pos >= state->token_count) {
    return tree;
  }

  Token current_token = tokens[state->pos];

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
      if (new_node == NULL) {
        return NULL; 
      }
      current_token = tokens[state->pos];

      consumed_token_node->right = new_node;
    }
    tree = consumed_token_node;
  }

  return tree;
}

AST_Node *parse_multiplicative(ParserState *state) {
  Token *tokens = state->tokens;
  Token current_token = tokens[state->pos];

  AST_Node *tree = parse_primary(state);
  if (tree == NULL) {
    return NULL;
  }

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
      AST_Node *new_node = parse_primary(state);
      if (new_node == NULL) {
        return NULL;
      }

      if (state->pos < state->token_count) {
        current_token = tokens[state->pos];
      }

      consumed_token_node->right = new_node;
    }
    tree = consumed_token_node;
  }

  return tree;
}

AST_Node *parse_primary(ParserState *state) {
  Token *tokens = state->tokens;
  Token current_token = tokens[state->pos];

  if (current_token.type == TOKEN_RIGHT_BRACKET) {
    state->error = PARSE_ERR_MISSING_BRACE;
    return NULL;
  }

  if (current_token.type != TOKEN_LEFT_BRACKET) {
    if (current_token.type != TOKEN_NUMBER) {
      state->error = PARSE_ERR_EXPECTED_NUMBER;
      return NULL;
    }
    AST_Node *num = AST_build_node_from_token(current_token);
    if (num == NULL) {
      state->error = PARSE_ERR_MEMORY_ALLOCATION;
    }
    state->pos++;
    return num;
  }

  state->pos++;
  if (state->pos == state->token_count) {
    state->error = PARSE_ERR_MISSING_BRACE;
    return NULL;
  }

  current_token = tokens[state->pos];
  if (current_token.type != TOKEN_NUMBER) {
    state->error = PARSE_ERR_EXPECTED_NUMBER;
    return NULL;
  }

  AST_Node *inner = parse_additive(state);
  if (state->pos == state->token_count) {
    state->error = PARSE_ERR_MISSING_BRACE;
    return NULL;
  }
  current_token = tokens[state->pos];
  if (current_token.type != TOKEN_RIGHT_BRACKET) {
    state->error = PARSE_ERR_MISSING_BRACE;
  } else {
    state->pos++;
  }

  return inner;
}