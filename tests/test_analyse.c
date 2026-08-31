#include "analyse.h"
#include "parser.h"
#include "test_utils.c"
#include "utils/data_structures/hashmap.h"
#include "utils/errors.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_analyse_bare_number();
void test_analyse_bare_undefined();
void test_analyse_assign_then_use();
void test_analyse_compound_undefined();

void test_analyse_if_discard();
void test_analyse_while_discard();
void test_analyse_if_reassignment_survives();
void test_analyse_nesting();

void test_analyse_propagate_condition();
void test_analyse_propagate_body();

void test_analyse_multi_statement_chain();
void test_analyse_double_insert_body();

int main() {
    // Base cases
    test_analyse_bare_number();
    test_analyse_bare_undefined();
    test_analyse_assign_then_use();
    test_analyse_compound_undefined();

    // Block discard logic
    test_analyse_if_discard();
    test_analyse_while_discard();
    test_analyse_if_reassignment_survives();
    test_analyse_nesting();

    // Propagation logic
    test_analyse_propagate_condition();
    test_analyse_propagate_body();

    test_analyse_multi_statement_chain();
    test_analyse_double_insert_body();

    printf("All analyse tests passed.\n");
    return 0;
}

void test_analyse_bare_number() {
    // Arrange
    char input[] = "5";
    ParserState *state = make_state_from_input(input);
    AST_Node *node = parse_statement(state);
    HashMap *set = HashMap_create();

    // Act
    AnalysisResult result = analyse(node, set);

    // Assert
    assert(result.error == SUCCESS);

    printf("test_analyse_bare_number passed.\n");
    free_state(state);
    HashMap_free(set);
}

void test_analyse_bare_undefined() {
    // Arrange
    char input[] = "y";
    ParserState *state = make_state_from_input(input);
    AST_Node *node = parse_statement(state);
    HashMap *set = HashMap_create();

    // Act
    AnalysisResult result = analyse(node, set);

    // Assert
    assert(result.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result.variable != NULL && strcmp(result.variable, "y") == 0);

    printf("test_analyse_bare_undefined passed.\n");
    free_state(state);
    HashMap_free(set);
}

void test_analyse_assign_then_use() {
    // Arrange
    char input1[] = "x = 5";
    ParserState *state1 = make_state_from_input(input1);
    AST_Node *node1 = parse_statement(state1);
    HashMap *set = HashMap_create();
    
    AnalysisResult result1 = analyse(node1, set);
    assert(result1.error == SUCCESS);

    char input2[] = "x + 1";
    ParserState *state2 = make_state_from_input(input2);
    AST_Node *node2 = parse_statement(state2);

    // Act
    AnalysisResult result2 = analyse(node2, set);

    // Assert
    assert(result2.error == SUCCESS);

    printf("test_analyse_assign_then_use passed.\n");
    free_state(state1);
    free_state(state2);
    HashMap_free(set);
}

void test_analyse_compound_undefined() {
    // Arrange
    char input[] = "y + 1";
    ParserState *state = make_state_from_input(input);
    AST_Node *node = parse_statement(state);
    HashMap *set = HashMap_create();

    // Act
    AnalysisResult result = analyse(node, set);

    // Assert
    assert(result.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result.variable != NULL && strcmp(result.variable, "y") == 0);

    printf("test_analyse_compound_undefined passed.\n");
    free_state(state);
    HashMap_free(set);
}

void test_analyse_if_discard() {
    // Arrange
    char input1[] = "if (1 > 0) { x = 5 }";
    ParserState *state1 = make_state_from_input(input1);
    HashMap *set = HashMap_create();
    analyse(parse_statement(state1), set);

    char input2[] = "x + 1";
    ParserState *state2 = make_state_from_input(input2);

    // Act
    AnalysisResult result2 = analyse(parse_statement(state2), set);

    // Assert
    assert(result2.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result2.variable != NULL && strcmp(result2.variable, "x") == 0);

    printf("test_analyse_if_discard passed.\n");
    free_state(state1);
    free_state(state2);
    HashMap_free(set);
}

void test_analyse_while_discard() {
    // Arrange
    char input1[] = "x = 1";
    ParserState *state1 = make_state_from_input(input1);
    HashMap *set = HashMap_create();
    analyse(parse_statement(state1), set);

    char input2[] = "while (x < 5) { y = 1 }";
    ParserState *state2 = make_state_from_input(input2);
    analyse(parse_statement(state2), set);

    char input3[] = "y + 1";
    ParserState *state3 = make_state_from_input(input3);

    // Act
    AnalysisResult result3 = analyse(parse_statement(state3), set);

    // Assert
    assert(result3.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result3.variable != NULL && strcmp(result3.variable, "y") == 0);

    printf("test_analyse_while_discard passed.\n");
    free_state(state1);
    free_state(state2);
    free_state(state3);
    HashMap_free(set);
}

void test_analyse_if_reassignment_survives() {
    // Arrange
    char input1[] = "x = 1";
    ParserState *state1 = make_state_from_input(input1);
    HashMap *set = HashMap_create();
    analyse(parse_statement(state1), set);

    char input2[] = "if (1 > 0) { x = 2 }";
    ParserState *state2 = make_state_from_input(input2);
    analyse(parse_statement(state2), set);

    char input3[] = "x + 1";
    ParserState *state3 = make_state_from_input(input3);

    // Act
    AnalysisResult result3 = analyse(parse_statement(state3), set);

    // Assert
    assert(result3.error == SUCCESS);

    printf("test_analyse_if_reassignment_survives passed.\n");
    free_state(state1);
    free_state(state2);
    free_state(state3);
    HashMap_free(set);
}

void test_analyse_nesting() {
    // Arrange
    char input1[] = "if (1 > 0) { x = 1 if (1 > 0) { y = 2 } x + 1 }";
    ParserState *state1 = make_state_from_input(input1);
    HashMap *set = HashMap_create();
    analyse(parse_statement(state1), set);

    char input2[] = "y";
    ParserState *state2 = make_state_from_input(input2);

    // Act
    AnalysisResult result2 = analyse(parse_statement(state2), set);

    // Assert
    assert(result2.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result2.variable != NULL && strcmp(result2.variable, "y") == 0);

    char input3[] = "x";
    ParserState *state3 = make_state_from_input(input3);
    AnalysisResult result3 = analyse(parse_statement(state3), set);
    assert(result3.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result3.variable != NULL && strcmp(result3.variable, "x") == 0);

    printf("test_analyse_nesting passed.\n");
    free_state(state1);
    free_state(state2);
    free_state(state3);
    HashMap_free(set);
}

void test_analyse_propagate_condition() {
    // Arrange
    char input[] = "if (x > 0) { y = 1 }";
    ParserState *state = make_state_from_input(input);
    HashMap *set = HashMap_create();

    // Act
    AnalysisResult result = analyse(parse_statement(state), set);

    // Assert
    assert(result.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result.variable != NULL && strcmp(result.variable, "x") == 0);

    printf("test_analyse_propagate_condition passed.\n");
    free_state(state);
    HashMap_free(set);
}

void test_analyse_propagate_body() {
    // Arrange
    char input[] = "if (1 > 0) { y = x + 1 }";
    ParserState *state = make_state_from_input(input);
    HashMap *set = HashMap_create();

    // Act
    AnalysisResult result = analyse(parse_statement(state), set);

    // Assert
    assert(result.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result.variable != NULL && strcmp(result.variable, "x") == 0);

    printf("test_analyse_propagate_body passed.\n");
    free_state(state);
    HashMap_free(set);
}

void test_analyse_multi_statement_chain() {
    // Arrange
    char input[] = "if (1 > 0) { a = 1 b = a + 1 c = b + 1 }";
    ParserState *state = make_state_from_input(input);
    HashMap *set = HashMap_create();

    // Act
    AnalysisResult result = analyse(parse_statement(state), set);

    // Assert
    assert(result.error == SUCCESS);

    printf("test_analyse_multi_statement_chain passed.\n");
    free_state(state);
    HashMap_free(set);
}

void test_analyse_double_insert_body() {
    // Arrange
    char input1[] = "if (1 > 0) { x = 1 x = 2 }";
    ParserState *state1 = make_state_from_input(input1);
    HashMap *set = HashMap_create();
    
    analyse(parse_statement(state1), set);

    char input2[] = "x + 1";
    ParserState *state2 = make_state_from_input(input2);

    // Act
    AnalysisResult result = analyse(parse_statement(state2), set);

    // Assert
    assert(result.error == EVALUATE_ERR_UNDEFINED_VARIABLE);
    assert(result.variable != NULL && strcmp(result.variable, "x") == 0);

    printf("test_analyse_double_insert_body passed.\n");
    free_state(state1);
    free_state(state2);
    HashMap_free(set);
}