#include "evaluate.h"
#include "parser.h"
#include "token.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_single_node_AST();
void test_multi_node_AST();
void test_division_by_zero();

int main() {
  test_single_node_AST();
  test_multi_node_AST();
  test_division_by_zero();

  printf("All evaluate tests passed.\n");
  return 0;
}

void test_single_node_AST() {
  // Arrange
  size_t count;
  char input[] = "1";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 7;
  state->pos = 0;

  AST_Node *node = parse_additive(state);

  // Act
  EvaluationResult result = evaluate(node);

  // Assert
  assert(result.result == 1);
  assert(result.error == SUCCESS);

  printf("test_single_node_AST passed.\n");
  free(tokens);
  free(state);
}

void test_multi_node_AST() {
  // Arrange
  size_t count;
  char input[] = "1+2*4-8/2";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 9;
  state->pos = 0;

  AST_Node *node = parse_additive(state);

  // Act
  EvaluationResult result = evaluate(node);

  // Assert
  assert(result.result == 5);
  assert(result.error == SUCCESS);

  printf("test_multi_node_AST passed.\n");
  free(tokens);
  free(state);
}

void test_division_by_zero() {
  // Arrange
  size_t count;
  char input[] = "1/0";
  Token *tokens = tokenise_string(input, &count);

  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = 7;
  state->pos = 0;

  AST_Node *node = parse_additive(state);

  // Act
  EvaluationResult result = evaluate(node);

  // Assert
  assert(result.error == EVALUATE_ERR_ZERO_DIVISION);

  printf("test_division_by_zero passed.\n");
  free(tokens);
  free(state);
}
