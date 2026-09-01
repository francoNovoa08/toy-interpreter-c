#include "codegen.h"
#include "utils/data_structures/AST.h"
#include <stdio.h>

static void codegen_internal(AST_Node *tree, FILE *file) {
  switch (tree->type) {
  case NODE_NUMBER:
    fprintf(file, "mov rax, %d\n", tree->data.number_value);
    fprintf(file, "push rax\n");
    return;
  case NODE_PLUS:
    codegen_internal(tree->left, file);
    codegen_internal(tree->right, file);
    fprintf(file, "pop rbx\n");
    fprintf(file, "pop rax\n");
    fprintf(file, "add rax, rbx\n");
    fprintf(file, "push rax\n");
    return;
  case NODE_MINUS:
    codegen_internal(tree->left, file);
    codegen_internal(tree->right, file);
    fprintf(file, "pop rbx\n");
    fprintf(file, "pop rax\n");
    fprintf(file, "sub rax, rbx\n");
    fprintf(file, "push rax\n");
    return;
  case NODE_TIMES:
    codegen_internal(tree->left, file);
    codegen_internal(tree->right, file);
    fprintf(file, "pop rbx\n");
    fprintf(file, "pop rax\n");
    fprintf(file, "imul rax, rbx\n");
    fprintf(file, "push rax\n");
    return;
  case NODE_OVER:
    codegen_internal(tree->left, file);
    codegen_internal(tree->right, file);
    fprintf(file, "pop rbx\n");
    fprintf(file, "pop rax\n");
    fprintf(file, "cqo\n");
    fprintf(file, "idiv rbx\n");
    fprintf(file, "push rax\n");
    return;
  default:
    return;
  }
}

void codegen(AST_Node *tree, const char *output_path) {
  FILE *file = fopen(output_path, "w");
  if (file == NULL) {
    return;
  }
  
  codegen_internal(tree, file);
  fclose(file);
}