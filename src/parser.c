#include "parser.h"
#include "utils/parser_utils.h"
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
    if (current_token.type == TOKEN_ASSIGNMENT) {
      state->error = PARSE_ERR_INVALID_ASSIGNMENT_TARGET;
      return NULL;
    }

    if (current_token.type == TOKEN_IDENTIFIER) {
      AST_Node *variable = AST_build_node_from_token(current_token);
      state->pos++;
      if (variable == NULL) {
        state->error = PARSE_ERR_MEMORY_ALLOCATION;
        return NULL;
      }

      return variable;
    }

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

  AST_Node *inner = parse_additive(state);

  if (inner == NULL) {
    return NULL;
  }

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

AST_Node *parse_statement(ParserState *state) {
  Token *tokens = state->tokens;
  Token current_token = tokens[state->pos];

  if (state->pos == state->token_count - 1) {
    return AST_build_node_from_token(current_token);
  }

  if (current_token.type != TOKEN_IDENTIFIER &&
      tokens[state->pos + 1].type == TOKEN_ASSIGNMENT) {
    state->error = PARSE_ERR_INVALID_ASSIGNMENT_TARGET;
    return NULL;
  }

  if (current_token.type == TOKEN_IF || current_token.type == TOKEN_WHILE) {
    return parse_conditional_block(state);
  }

  if (!(current_token.type == TOKEN_IDENTIFIER &&
        tokens[state->pos + 1].type == TOKEN_ASSIGNMENT)) {
    return parse_comparison(state);
  }

  AST_Node *variable = AST_build_node_from_token(current_token);
  if (variable == NULL) {
    state->error = PARSE_ERR_MEMORY_ALLOCATION;
  }
  state->pos++;
  current_token = tokens[state->pos];
  AST_Node *assign = AST_build_node_from_token(current_token);
  if (assign == NULL) {
    state->error = PARSE_ERR_MEMORY_ALLOCATION;
  }
  state->pos++;

  assign->left = variable;
  AST_Node *right = parse_comparison(state);
  if (right == NULL) {
    return NULL;
  }
  assign->right = right;
  return assign;
}

AST_Node *parse_comparison(ParserState *state) {
  AST_Node *tree_left = parse_additive(state);
  if (tree_left == NULL) {
    return NULL;
  }

  Token *tokens = state->tokens;
  Token current_token = tokens[state->pos];
  if (current_token.type != TOKEN_EQUALS &&
      current_token.type != TOKEN_GREATER_THAN &&
      current_token.type != TOKEN_GREATER_THAN_OR_EQUAL &&
      current_token.type != TOKEN_LESS_THAN &&
      current_token.type != TOKEN_LESS_THAN_OR_EQUAL &&
      current_token.type != TOKEN_NOT_EQUAL) {
    return tree_left;
  }

  AST_Node *comparison_node = AST_build_node_from_token(current_token);
  state->pos++;
  current_token = tokens[state->pos];
  AST_Node *tree_right = parse_additive(state);
  if (tree_right == NULL) {
    return NULL;
  }

  comparison_node->left = tree_left;
  comparison_node->right = tree_right;
  return comparison_node;
}