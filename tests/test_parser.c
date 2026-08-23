#include "parser.h"
#include "token.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_multiplicative_single_operator();
void test_multiplicative_multiple_operands();
void test_multiplicative_malformed_operands();
void test_multiplicative_single_operand();
void test_multiplicative_no_relevant_operands();

void test_additive_single_operator();
void test_additive_multiple_operands();
void test_additive_single_operand();
void test_additive_no_relevant_operators();

void test_parenthesised_expression();
void test_invalid_parenthesis();

int main() {
  setbuf(stdout, NULL);
  // parse_multiplicative_tests
  test_multiplicative_single_operator();
  test_multiplicative_multiple_operands();
  test_multiplicative_malformed_operands();
  test_multiplicative_single_operand();
  test_multiplicative_no_relevant_operands();

  // parse_additive tests
  test_additive_single_operator();
  test_additive_multiple_operands();
  test_additive_single_operand();
  test_additive_no_relevant_operators();

  // Parenthesis tests
  test_parenthesised_expression();
  test_invalid_parenthesis();

  printf("All parser tests passed.\n");
  return 0;
}

void test_multiplicative_single_operator() {
  // Arrange
  Token *token_array = malloc(sizeof(Token) * 3);

  token_array[0].value = 10;
  token_array[0].type = TOKEN_NUMBER;

  token_array[1].type = TOKEN_OVER;

  token_array[2].value = 5;
  token_array[2].type = TOKEN_NUMBER;

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = token_array;
  state->token_count = 3;
  state->pos = 0;

  // Act
  AST_Node *node = parse_multiplicative(state);

  // Assert
  assert(node->type == NODE_OVER);
  assert(node->left->data.number_value == 10);
  assert(node->left->type == NODE_NUMBER);
  assert(node->right->data.number_value == 5);
  assert(state->pos == 3);

  printf("test_multiplicative_single_operator passed.\n");
  free(token_array);
  free(state);
}

void test_multiplicative_multiple_operands() {
  // Arrange
  size_t count;
  char input[] = "1*2/3+4";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 7;
  state->pos = 0;

  // Act
  AST_Node *node = parse_multiplicative(state);

  // Assert
  assert(node->type == NODE_OVER);
  assert(node->left->type == NODE_TIMES);
  assert(node->left->left->data.number_value == 1);
  assert(node->left->right->data.number_value == 2);
  assert(node->left->right->type == NODE_NUMBER);
  assert(node->right->data.number_value == 3);
  assert(state->pos == 5);

  printf("test_multiplicative_multiple_operands passed.\n");
  free(tokens);
  free(state);
}

void test_multiplicative_malformed_operands() {
  // Arrange
  size_t count;
  char input[] = "1*/2";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 4;
  state->pos = 0;

  // Act
  AST_Node *node = parse_multiplicative(state);

  // Assert
  assert(node == NULL);

  printf("test_multiplicative_malformed_operands passed.\n");
  free(tokens);
  free(state);
}

void test_multiplicative_single_operand() {
  // Arrange
  size_t count;
  char input[] = "1";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 1;
  state->pos = 0;

  // Act
  AST_Node *node = parse_multiplicative(state);

  // Assert
  assert(node->data.number_value == 1);
  assert(node->type == NODE_NUMBER);
  assert(state->pos == 1);

  printf("test_multiplicative_single_operand passed.\n");
  free(tokens);
  free(state);
}

void test_multiplicative_no_relevant_operands() {
  // Arrange
  size_t count;
  char input[] = "1+2";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 3;
  state->pos = 0;

  // Act
  AST_Node *node = parse_multiplicative(state);

  // Assert
  assert(node->type == NODE_NUMBER);
  assert(node->data.number_value == 1);
  assert(state->pos == 1);

  printf("test_multiplicative_no_relevant_operands passed.\n");
  free(tokens);
  free(state);
}

void test_additive_single_operator() {
  // Arrange
  Token *token_array = malloc(sizeof(Token) * 3);

  token_array[0].value = 10;
  token_array[0].type = TOKEN_NUMBER;

  token_array[1].type = TOKEN_PLUS;

  token_array[2].value = 5;
  token_array[2].type = TOKEN_NUMBER;

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = token_array;
  state->token_count = 3;
  state->pos = 0;

  // Act
  AST_Node *node = parse_additive(state);

  // Assert
  assert(node->type == NODE_PLUS);
  assert(node->left->data.number_value == 10);
  assert(node->left->type == NODE_NUMBER);
  assert(node->right->data.number_value == 5);
  assert(state->pos == state->token_count);

  printf("test_additive_single_operator passed.\n");
  free(token_array);
  free(state);
}

void test_additive_multiple_operands() {
  // Arrange
  size_t count;
  char input[] = "1+2-3*4";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 7;
  state->pos = 0;

  // Act
  AST_Node *node = parse_additive(state);

  // Assert
  assert(node->type == NODE_MINUS);
  assert(node->right->type == NODE_TIMES);
  assert(node->left->type == NODE_PLUS);
  assert(node->left->left->data.number_value == 1);
  assert(node->left->right->data.number_value == 2);
  assert(node->left->right->type == NODE_NUMBER);
  assert(node->right->left->data.number_value == 3);
  assert(node->right->right->data.number_value == 4);
  assert(state->pos == state->token_count);

  printf("test_additive_multiple_operands passed.\n");
  free(tokens);
  free(state);
}

void test_additive_single_operand() {
  // Arrange
  size_t count;
  char input[] = "1";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 1;
  state->pos = 0;

  // Act
  AST_Node *node = parse_additive(state);

  // Assert
  assert(node->data.number_value == 1);
  assert(node->type == NODE_NUMBER);
  assert(state->pos == state->token_count);

  printf("test_additive_single_operand passed.\n");
  free(tokens);
  free(state);
}

void test_additive_no_relevant_operators() {
  // Arrange
  size_t count;
  char input[] = "1/2";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 3;
  state->pos = 0;

  // Act
  AST_Node *node = parse_additive(state);

  // Assert
  assert(node->type == NODE_OVER);
  assert(node->left->data.number_value == 1);
  assert(node->right->data.number_value == 2);
  assert(state->pos == state->token_count);

  printf("test_additive_no_relevant_operators passed.\n");
  free(tokens);
  free(state);
}

void test_parenthesised_expression() {
  // Arrange
  size_t count;
  char input[] = "1*(2+3)-4";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 9;
  state->pos = 0;

  // Act
  AST_Node *node = parse_additive(state);

  // Assert
  assert(node->type == NODE_MINUS);
  assert(node->left->type == NODE_TIMES);
  assert(node->left->right->type == NODE_PLUS);
  assert(node->left->right->right->data.number_value == 3);
  assert(state->pos == state->token_count);

  printf("test_parenthesised_expression passed.\n");
  free(tokens);
  free(state);
}

void test_invalid_parenthesis() {
  // Arrange
  size_t count;
  char input[] = "(1+2";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 4;
  state->pos = 0;

  // Act
  AST_Node *node = parse_additive(state);

  // Assert
  assert(node == NULL);
  assert(state->error == PARSE_ERR_MISSING_BRACE);

  printf("test_invalid_parenthesis passed.\n");
  free(tokens);
  free(state);
}