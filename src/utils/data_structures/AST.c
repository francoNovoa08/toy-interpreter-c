#include "utils/data_structures/AST.h"
#include <stdlib.h>

AST_Node *AST_build_node_from_token(Token token) {
  AST_Node *new_node = malloc(sizeof(AST_Node));
  switch (token.type) {
  case TOKEN_NUMBER:
    new_node->type = NODE_NUMBER;
    new_node->data.number_value = token.value.number_value;
    break;
  case TOKEN_TIMES:
    new_node->type = NODE_TIMES;
    break;
  case TOKEN_OVER:
    new_node->type = NODE_OVER;
    break;
  case TOKEN_PLUS:
    new_node->type = NODE_PLUS;
    break;
  case TOKEN_MINUS:
    new_node->type = NODE_MINUS;
    break;
  case TOKEN_IDENTIFIER:
    new_node->type = NODE_VARIABLE;
    new_node->data.identifier.length = token.value.identifier.length;
    new_node->data.identifier.start = token.value.identifier.start;
    break;
  case TOKEN_ASSIGNMENT:
    new_node->type = NODE_ASSIGN;
    break;
  default:
    return NULL;
  }

  return new_node;
}