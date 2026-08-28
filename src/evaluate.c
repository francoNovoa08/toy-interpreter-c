#include "evaluate.h"
#include "utils/evaluate_utils.h"

EvaluationResult evaluate(AST_Node *tree, SymbolTable *table) {
  EvaluationResult result;
  if (tree->type == NODE_NUMBER) {
    result.result = tree->data.number_value;
    result.error = SUCCESS;
    return result;
  }

  if (tree->type == NODE_VARIABLE) {
    char *name = get_variable_name(tree->data.identifier.start,
                                   tree->data.identifier.length);

    if (name == NULL) {
      result.error = EVALUATE_ERR_MEMORY_ALLOCATION;
      return result;
    }
    int out_value;
    if (!(SymbolTable_get(table, name, &out_value))) {
      result.error = EVALUATE_ERR_UNDEFINED_VARIABLE;
    } else {
      result.result = out_value;
      result.error = SUCCESS;
    }

    return result;
  }

  if (tree->type == NODE_ASSIGN) {
    char *name = get_variable_name(tree->left->data.identifier.start,
                                   tree->left->data.identifier.length);

    if (name == NULL) {
      result.error = EVALUATE_ERR_MEMORY_ALLOCATION;
      return result;
    }

    EvaluationResult assignment_result = evaluate(tree->right, table);
    if (assignment_result.error == SUCCESS) {
      SymbolTable_assign(table, name, assignment_result.result);
    }

    return assignment_result;
  }

  EvaluationResult left_result = evaluate(tree->left, table);
  if (left_result.error != SUCCESS)
    return left_result;

  EvaluationResult right_result = evaluate(tree->right, table);
  if (right_result.error != SUCCESS)
    return right_result;

  switch (tree->type) {
  case NODE_PLUS:
    result.result = left_result.result + right_result.result;
    result.error = SUCCESS;
    return result;
  case NODE_MINUS:
    result.result = left_result.result - right_result.result;
    result.error = SUCCESS;
    return result;
  case NODE_TIMES:
    result.result = left_result.result * right_result.result;
    result.error = SUCCESS;
    return result;
  case NODE_OVER:
    if (right_result.result == 0) {
      result.error = EVALUATE_ERR_ZERO_DIVISION;
    } else {
      result.result = left_result.result / right_result.result;
      result.error = SUCCESS;
    }
    return result;
  default:
    result.error = EVALUATE_ERR_UNKNOWN_NODE;
    result.result = 0;
    return result;
  }
}