#include "utils/AST.h"
#include <stdlib.h>

AST_Node *AST_build_node_from_token(Token token) {
  AST_Node *new_node = malloc(sizeof(AST_Node));
  switch (token.type) {
  case TOKEN_NUMBER:
    new_node->type = NODE_NUMBER;
    new_node->data.number_value = token.value;
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
  default:
    return NULL;
  }

  return new_node;
}