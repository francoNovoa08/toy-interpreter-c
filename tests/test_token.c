#include "token.h"
#include <assert.h>
#include <stdio.h>

void test_simple_addition();
void test_multi_digit_numbers();
void test_whitespace();

int main() {
    test_simple_addition();
    test_multi_digit_numbers();
    test_whitespace();

    printf("All token tests passed.\n");
    return 0;
}

void test_simple_addition() {
    size_t count;
    char input[] = "3+4";
    Token *tokens = tokenise_string(input, &count);

    assert(count == 3);
    assert(tokens[0].type == TOKEN_NUMBER);
    assert(tokens[0].value == 3);
    assert(tokens[1].type == TOKEN_PLUS);
    assert(tokens[2].value == 4);
    printf("test_simple_addition passed.\n");
}

void test_multi_digit_numbers() {
    size_t count;
    char input[] = "23*123/2-12";
    Token *tokens = tokenise_string(input, &count);

    assert(count == 7);
    assert(tokens[1].type == TOKEN_TIMES);
    assert(tokens[2].value == 123);
    assert(tokens[3].type == TOKEN_OVER);
    assert(tokens[5].type == TOKEN_MINUS);
    assert(tokens[6].value == 12);
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