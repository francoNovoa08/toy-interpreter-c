#ifndef AST_H
#define AST_H

typedef enum {
    NODE_NUMBER,
    NODE_PLUS,
    NODE_MINUS,
    NODE_TIMES,
    NODE_OVER,
} NodeType;

typedef struct AST_Node {
    NodeType type;
    union {
        int number_value;
    } data;
    struct AST_Node* left;
    struct AST_Node* right;
} AST_Node;

#endif // AST_H