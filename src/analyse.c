#include "analyse.h"
#include "utils/data_structures/vector.h"
#include "utils/evaluate_utils.h"

static AnalysisResult analyse_internal(AST_Node *tree, HashMap *set,
                                       Vector *seen_list) {
  AnalysisResult result;

  if (tree->type == NODE_VARIABLE) {
    char *name = get_variable_name(tree->data.identifier.start,
                                   tree->data.identifier.length);
    if (name == NULL) {
      result.error = EVALUATE_ERR_MEMORY_ALLOCATION;
      return result;
    }

    int out_value;

    if (HashMap_get(set, name, &out_value)) {
      result.error = SUCCESS;
      return result;
    } else {
      result.error = EVALUATE_ERR_UNDEFINED_VARIABLE;
      result.variable = name;
      return result;
    }
  }

  if (tree->type == NODE_ASSIGN) {
    char *name = get_variable_name(tree->left->data.identifier.start,
                                   tree->left->data.identifier.length);

    if (name == NULL) {
      result.error = EVALUATE_ERR_MEMORY_ALLOCATION;
      return result;
    }

    AnalysisResult assignment_result =
        analyse_internal(tree->right, set, seen_list);
    if (assignment_result.error != SUCCESS) {
      return assignment_result;
    }

    int out_value;
    if (!HashMap_get(set, name, &out_value) && seen_list != NULL) {
      Vector_push(seen_list, name);
    }
    if (!HashMap_insert(set, name, 1)) {
      result.error = EVALUATE_ERR_MEMORY_ALLOCATION;
    } else {
      result.error = SUCCESS;
    }

    return result;
  }

  if (tree->type == NODE_STATEMENT_LIST) {
    AnalysisResult left_result = analyse_internal(tree->left, set, seen_list);
    if (left_result.error != SUCCESS) {
      return left_result;
    }

    if (tree->right != NULL) {
      AnalysisResult right_result =
          analyse_internal(tree->right, set, seen_list);
      return right_result;
    }

    return left_result;
  }

  switch (tree->type) {
  case NODE_PLUS:
  case NODE_MINUS:
  case NODE_TIMES:
  case NODE_OVER:
  case NODE_GREATER_THAN:
  case NODE_LESS_THAN:
  case NODE_GREATER_THAN_OR_EQUAL:
  case NODE_LESS_THAN_OR_EQUAL:
  case NODE_EQUALS:
  case NODE_NOT_EQUAL: {
    AnalysisResult left_result = analyse_internal(tree->left, set, seen_list);
    if (left_result.error != SUCCESS) {
      return left_result;
    }

    AnalysisResult right_result = analyse_internal(tree->right, set, seen_list);
    if (right_result.error != SUCCESS) {
      return right_result;
    }

    result.error = SUCCESS;
    return result;
  }
  case NODE_NUMBER:
    result.error = SUCCESS;
    return result;
  case NODE_IF:
  case NODE_WHILE: {
    AnalysisResult left_result = analyse_internal(tree->left, set, seen_list);
    if (left_result.error != SUCCESS) {
      return left_result;
    }

    Vector new_seen_list;
    if (!Vector_init(&new_seen_list)) {
      result.error = EVALUATE_ERR_MEMORY_ALLOCATION;
      return result;
    }
    AnalysisResult right_result =
        analyse_internal(tree->right, set, &new_seen_list);
    if (right_result.error != SUCCESS) {
      return right_result;
    }

    for (size_t i = 0; i < new_seen_list.size; i++) {
      HashMap_delete(set, Vector_get(&new_seen_list, i));
    }
    Vector_free(&new_seen_list);

    result.error = SUCCESS;
    return result;
  }
  default:
    result.error = EVALUATE_ERR_UNKNOWN_NODE;
    return result;
    break;
  }
}

AnalysisResult analyse(AST_Node *tree, HashMap *set) {
  return analyse_internal(tree, set, NULL);
}
