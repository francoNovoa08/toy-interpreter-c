#include "codegen.h"
#include "parser.h"
#include "test_utils.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_single_number();
void test_addition();
void test_subtraction();
void test_multiplication();
void test_division();

int main() {
  test_single_number();
  test_addition();
  test_subtraction();
  test_multiplication();
  test_division();

  printf("All codegen tests passed.\n");
  return 0;
}

void test_addition() {
  // Arrange
  char input[] = "3+4";
  ParserState *state = make_state_from_input(input);
  AST_Node *tree = parse_statement(state);
  char *output_path = "test_output.s";

  // Act
  codegen(tree, output_path);
  /*
    Should produce:
    mov rax, 3
    push rax
    mov rax, 4
    push rax
    pop rbx
    pop rax
    add rax, rbx
    push rax
  */
  char *file_contents = read_assembly_file(output_path);
  assert(file_contents != NULL);
  char *number_location = strstr(file_contents, "3");
  char *push_location = strstr(file_contents, "push");
  char *number_location2 = strstr(number_location + 1, "4");
  char *push_location2 = strstr(push_location + 1, "push");
  char *pop_location = strstr(push_location2 + 1, "pop");
  char *pop_location2 = strstr(pop_location + 1, "pop");
  char *add_location = strstr(pop_location2 + 1, "add");
  char *final_push = strstr(push_location2 + 1, "push");

  // Assert
  assert(number_location != NULL);
  assert(push_location != NULL);
  assert(number_location2 != NULL);
  assert(push_location2 != NULL);
  assert(pop_location != NULL);
  assert(pop_location2 != NULL);
  assert(add_location != NULL);
  assert(final_push != NULL);
  assert(number_location < push_location);
  assert(push_location < number_location2);
  assert(number_location2 < push_location2);
  assert(push_location2 < pop_location);
  assert(pop_location < pop_location2);
  assert(add_location < final_push);

  printf("test_addition passed.\n");

  remove(output_path);
  free(file_contents);
  free_state(state);
}

void test_single_number() {
  // Arrange
  char input[] = "5";
  ParserState *state = make_state_from_input(input);
  AST_Node *tree = parse_statement(state);
  char *output_path = "test_output.s";

  // Act
  codegen(tree, output_path); // Should produce: mov rax, 5; push rax;
  char *file_contents = read_assembly_file(output_path);
  assert(file_contents != NULL);
  char *number_location = strstr(file_contents, "5");
  char *push_location = strstr(file_contents, "push");

  // Assert
  assert(number_location != NULL);
  assert(push_location != NULL);
  assert(number_location < push_location);

  printf("test_single_number passed.\n");

  remove(output_path);
  free(file_contents);
  free_state(state);
}

void test_subtraction() {
  // Arrange
  char input[] = "5-2";
  ParserState *state = make_state_from_input(input);
  AST_Node *tree = parse_statement(state);
  char *output_path = "test_output.s";

  // Act
  codegen(tree, output_path);
  /*
    Should produce:
    mov rax, 5
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    sub rax, rbx
    push rax
  */
  char *file_contents = read_assembly_file(output_path);
  assert(file_contents != NULL);
  char *number_location = strstr(file_contents, "5");
  char *push_location = strstr(file_contents, "push");
  char *number_location2 = strstr(number_location + 1, "2");
  char *push_location2 = strstr(push_location + 1, "push");
  char *pop_location = strstr(push_location2 + 1, "pop");
  char *pop_location2 = strstr(pop_location + 1, "pop");
  char *sub_location = strstr(pop_location2 + 1, "sub");
  char *final_push = strstr(push_location2 + 1, "push");

  // Assert
  assert(number_location != NULL);
  assert(push_location != NULL);
  assert(number_location2 != NULL);
  assert(push_location2 != NULL);
  assert(pop_location != NULL);
  assert(pop_location2 != NULL);
  assert(sub_location != NULL);
  assert(final_push != NULL);
  assert(number_location < push_location);
  assert(push_location < number_location2);
  assert(number_location2 < push_location2);
  assert(push_location2 < pop_location);
  assert(pop_location < pop_location2);
  assert(sub_location < final_push);

  printf("test_subtraction passed.\n");

  remove(output_path);
  free(file_contents);
  free_state(state);
}

void test_multiplication() {
  // Arrange
  char input[] = "3*4";
  ParserState *state = make_state_from_input(input);
  AST_Node *tree = parse_statement(state);
  char *output_path = "test_output.s";

  // Act
  codegen(tree, output_path);
  /*
    Should produce:
    mov rax, 3
    push rax
    mov rax, 4
    push rax
    pop rbx
    pop rax
    imul rax, rbx
    push rax
  */
  char *file_contents = read_assembly_file(output_path);
  assert(file_contents != NULL);
  char *number_location = strstr(file_contents, "3");
  char *push_location = strstr(file_contents, "push");
  char *number_location2 = strstr(number_location + 1, "4");
  char *push_location2 = strstr(push_location + 1, "push");
  char *pop_location = strstr(push_location2 + 1, "pop");
  char *pop_location2 = strstr(pop_location + 1, "pop");
  char *imul_location = strstr(pop_location2 + 1, "imul");
  char *final_push = strstr(push_location2 + 1, "push");

  // Assert
  assert(number_location != NULL);
  assert(push_location != NULL);
  assert(number_location2 != NULL);
  assert(push_location2 != NULL);
  assert(pop_location != NULL);
  assert(pop_location2 != NULL);
  assert(imul_location != NULL);
  assert(final_push != NULL);
  assert(number_location < push_location);
  assert(push_location < number_location2);
  assert(number_location2 < push_location2);
  assert(push_location2 < pop_location);
  assert(pop_location < pop_location2);
  assert(imul_location < final_push);

  printf("test_multiplication passed.\n");

  remove(output_path);
  free(file_contents);
  free_state(state);
}

void test_division() {
  // Arrange
  char input[] = "10/3";
  ParserState *state = make_state_from_input(input);
  AST_Node *tree = parse_statement(state);
  char *output_path = "test_output.s";

  // Act
  codegen(tree, output_path);
  /*
    Should produce:
    mov rax, 10
    push rax
    mov rax, 3
    push rax
    pop rbx
    pop rax
    cqo
    idiv rbx
    push rax
  */
  char *file_contents = read_assembly_file(output_path);
  assert(file_contents != NULL);
  char *number_location = strstr(file_contents, "10");
  char *push_location = strstr(file_contents, "push");
  char *number_location2 = strstr(number_location + 1, "3");
  char *push_location2 = strstr(push_location + 1, "push");
  char *pop_location = strstr(push_location2 + 1, "pop");
  char *pop_location2 = strstr(pop_location + 1, "pop");
  char *cqo_location = strstr(pop_location2 + 1, "cqo");
  char *idiv_location = strstr(cqo_location, "idiv");
  char *final_push = strstr(push_location2 + 1, "push");

  // Assert
  assert(number_location != NULL);
  assert(push_location != NULL);
  assert(number_location2 != NULL);
  assert(push_location2 != NULL);
  assert(pop_location != NULL);
  assert(pop_location2 != NULL);
  assert(idiv_location != NULL);
  assert(final_push != NULL);
  assert(cqo_location != NULL);
  assert(number_location < push_location);
  assert(push_location < number_location2);
  assert(number_location2 < push_location2);
  assert(push_location2 < pop_location);
  assert(pop_location < pop_location2);
  assert(idiv_location < final_push);
  assert(cqo_location < idiv_location);

  printf("test_division passed.\n");

  remove(output_path);
  free(file_contents);
  free_state(state);
}