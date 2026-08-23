#include "evaluate.h"

EvaluationResult evaluate(AST_Node *tree) {
  EvaluationResult result;
  if (tree->type == NODE_NUMBER) {
    result.result = tree->data.number_value;
    result.error = SUCCESS;
    return result;
  }

  EvaluationResult left_result = evaluate(tree->left);
  if (left_result.error != SUCCESS)
    return left_result;

  EvaluationResult right_result = evaluate(tree->right);
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