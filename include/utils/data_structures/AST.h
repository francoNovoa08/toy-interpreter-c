#ifndef AST_H
#define AST_H

#include "token.h"
typedef enum {
  NODE_NUMBER,
  NODE_PLUS,
  NODE_MINUS,
  NODE_TIMES,
  NODE_OVER,
  NODE_VARIABLE,
  NODE_ASSIGN,
  NODE_GREATER_THAN,
  NODE_LESS_THAN,
  NODE_EQUALS,
  NODE_GREATER_THAN_OR_EQUAL,
  NODE_LESS_THAN_OR_EQUAL,
  NODE_NOT_EQUAL,
  NODE_STATEMENT_LIST,
  NODE_IF,
} NodeType;

typedef struct AST_Node {
  NodeType type;
  union {
    int number_value;
    struct {
      const char *start;
      size_t length;
    } identifier;
  } data;
  struct AST_Node *left;
  struct AST_Node *right;
} AST_Node;

AST_Node *AST_build_node_from_token(Token token);

#endif // AST_H