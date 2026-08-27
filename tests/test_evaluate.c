#include "evaluate.h"
#include "parser.h"
#include "test_utils.c"
#include "utils/data_structures/symbol_table.h"
#include <assert.h>
#include <stdio.h>

void test_single_node_AST();
void test_multi_node_AST();
void test_division_by_zero();

void test_simple_assignment();
void test_variable_persistence();
void test_unassigned_variable();
void test_assignment_failure();

int main() {
  test_single_node_AST();
  test_multi_node_AST();
  test_division_by_zero();

  test_simple_assignment();
  test_variable_persistence();
  test_unassigned_variable();
  test_assignment_failure();

  printf("All evaluate tests passed.\n");
  return 0;
}

void test_single_node_AST() {
  // Arrange
  char input[] = "1";

  ParserState *state = make_state_from_input(input);
  AST_Node *node = parse_statement(state);
  SymbolTable *table = SymbolTable_create();

  // Act
  EvaluationResult result = evaluate(node, table);

  // Assert
  assert(result.result == 1);
  assert(result.error == SUCCESS);

  printf("test_single_node_AST passed.\n");
  free_state(state);
  free(table);
}

void test_multi_node_AST() {
  // Arrange
  char input[] = "1+2*4-8/2";
  ParserState *state = make_state_from_input(input);
  AST_Node *node = parse_statement(state);
  SymbolTable *table = SymbolTable_create();

  // Act
  EvaluationResult result = evaluate(node, table);

  // Assert
  assert(result.result == 5);
  assert(result.error == SUCCESS);

  printf("test_multi_node_AST passed.\n");
  free_state(state);
  free(table);
}

void test_division_by_zero() {
  // Arrange
  char input[] = "1/0";
  ParserState *state = make_state_from_input(input);
  AST_Node *node = parse_statement(state);
  SymbolTable *table = SymbolTable_create();

  // Act
  EvaluationResult result = evaluate(node, table);

  // Assert
  assert(result.error == EVALUATE_ERR_ZERO_DIVISION);

  printf("test_division_by_zero passed.\n");
  free_state(state);
  free(table);
}

void test_simple_assignment() {
  // Arrange
  char input[] = "x=5";
  ParserState *state = make_state_from_input(input);
  AST_Node *node = parse_statement(state);
  SymbolTable *table = SymbolTable_create();
  int out_value;

  // Act
  EvaluationResult result = evaluate(node, table);

  // Assert
  assert(result.result == 5);
  assert(SymbolTable_get(table, "x", &out_value) == true);
  assert(out_value == 5);

  printf("test_simple_assignment passed.\n");
  free_state(state);
  free(table);
}

void test_variable_persistence() {
  // Arrange
  char input[] = "x=5";
  ParserState *state = make_state_from_input(input);
  AST_Node *node = parse_statement(state);
  SymbolTable *table = SymbolTable_create();
  int out_value;
  EvaluationResult result = evaluate(node, table);

  char input2[] = "x+3";
  ParserState *state2 = make_state_from_input(input2);
  AST_Node *node2 = parse_statement(state2);

  // Act
  EvaluationResult result2 = evaluate(node2, table);

  // Assert
  assert(result2.result == 8);
  assert(SymbolTable_get(table, "x", &out_value) == true);
  assert(out_value == 5);

  printf("test_variable_persistence passed.\n");
  free_state(state);
  free(table);
}

void test_unassigned_variable() {
  // Arrange
  char input[] = "y+1";
  ParserState *state = make_state_from_input(input);
  AST_Node *node = parse_statement(state);
  SymbolTable *table = SymbolTable_create();

  // Act
  EvaluationResult result = evaluate(node, table);

  // Assert
  assert(result.error == EVALUATE_ERR_UNDEFINED_VARIABLE);

  printf("test_unassigned_variable passed.\n");
  free_state(state);
  free(table);
}

void test_assignment_failure() {
  // Arrange
  char input[] = "x=1/0";
  ParserState *state = make_state_from_input(input);
  AST_Node *node = parse_statement(state);
  SymbolTable *table = SymbolTable_create();
  int out_value;

  // Act
  EvaluationResult result = evaluate(node, table);

  // Assert
  assert(result.error == EVALUATE_ERR_ZERO_DIVISION);
  assert(SymbolTable_get(table, "x", &out_value) == false);

  printf("test_assignment_failure passed.\n");
  free_state(state);
  free(table);
}