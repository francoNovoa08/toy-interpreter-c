#include "token.h"
#include <assert.h>
#include <stdio.h>

void test_simple_addition();
void test_multi_digit_numbers();
void test_whitespace();
void test_parenthesis();
void test_assignment();
void test_multi_character_identifier();
void test_conditionals();

int main() {
  test_simple_addition();
  test_multi_digit_numbers();
  test_whitespace();
  test_parenthesis();
  test_assignment();
  test_multi_character_identifier();

  printf("All token tests passed.\n");
  return 0;
}

void test_simple_addition() {
  size_t count;
  char input[] = "3+4";
  Token *tokens = tokenise_string(input, &count);

  assert(count == 3);
  assert(tokens[0].type == TOKEN_NUMBER);
  assert(tokens[0].value.number_value == 3);
  assert(tokens[1].type == TOKEN_PLUS);
  assert(tokens[2].value.number_value == 4);
  printf("test_simple_addition passed.\n");
}

void test_multi_digit_numbers() {
  size_t count;
  char input[] = "23*123/2-12";
  Token *tokens = tokenise_string(input, &count);

  assert(count == 7);
  assert(tokens[1].type == TOKEN_TIMES);
  assert(tokens[2].value.number_value == 123);
  assert(tokens[3].type == TOKEN_OVER);
  assert(tokens[5].type == TOKEN_MINUS);
  assert(tokens[6].value.number_value == 12);
  printf("test_multi_digit_numbers passed.\n");
}

void test_whitespace() {
  size_t count;
  char input[] = "+ - * /";
  Token *tokens = tokenise_string(input, &count);

  assert(count == 4);
  assert(tokens[0].type == TOKEN_PLUS);
  assert(tokens[1].type == TOKEN_MINUS);
  assert(tokens[2].type == TOKEN_TIMES);
  assert(tokens[3].type == TOKEN_OVER);
  printf("test_whitespace passed.\n");
}

void test_parenthesis() {
  size_t count;
  char input[] = "1(2)3";
  Token *tokens = tokenise_string(input, &count);
  assert(count == 5);
  assert(tokens[1].type == TOKEN_LEFT_BRACKET);
  assert(tokens[2].type == TOKEN_NUMBER);
  assert(tokens[3].type == TOKEN_RIGHT_BRACKET);
  assert(tokens[4].type == TOKEN_NUMBER);
  printf("test_parenthesis passed.\n");
}

void test_assignment() {
  size_t count;
  char input[] = "x=2+3";
  Token *tokens = tokenise_string(input, &count);

  assert(count == 5);
  assert(tokens[0].type == TOKEN_IDENTIFIER);
  assert(tokens[0].value.identifier.length == 1);
  assert(tokens[1].type == TOKEN_ASSIGNMENT);
  assert(tokens[2].type == TOKEN_NUMBER);
  assert(tokens[3].type == TOKEN_PLUS);
  assert(tokens[4].type == TOKEN_NUMBER);

  printf("test_assignment passed.\n");
}

void test_multi_character_identifier() {
  size_t count;
  char input[] = "count = 10";
  Token *tokens = tokenise_string(input, &count);

  assert(count == 3);
  assert(tokens[0].type == TOKEN_IDENTIFIER);
  assert(tokens[0].value.identifier.length == 5);
  assert(tokens[1].type == TOKEN_ASSIGNMENT);
  assert(tokens[2].type == TOKEN_NUMBER);

  printf("test_multi_character_identifier passed.\n");
}

void test_conditionals() {
  size_t count;
  char input[] = "2==5<1>";
  Token *tokens = tokenise_string(input, &count);

  assert(count == 6);
  assert(tokens[0].type == TOKEN_NUMBER);
  assert(tokens[1].type == TOKEN_EQUALS);
  assert(tokens[2].type == TOKEN_NUMBER);
  assert(tokens[2].value.number_value == 5);
  assert(tokens[3].type == TOKEN_LESS_THAN);
  assert(tokens[4].type == TOKEN_NUMBER);
  assert(tokens[4].value.number_value == 1);
  assert(tokens[5].type == TOKEN_GREATER_THAN);

  printf("test_conditionals passed.\n");
}