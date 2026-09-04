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
  
  fprintf(file, ".intel_syntax noprefix\n");
  fprintf(file, ".section .data\n");
  fprintf(file, "fmt: .string \"%%d\\n\"\n");
  fprintf(file, ".section .text\n");
  fprintf(file, ".globl main\n");
  fprintf(file, "main:\n");
  fprintf(file, "push rbp\n");

  codegen_internal(tree, file);

  fprintf(file, "pop rsi\n");
  fprintf(file, "lea rdi, [rip + fmt]\n");
  fprintf(file, "call printf\n");
  fprintf(file, "mov eax, 0\n");
  fprintf(file, "pop rbp\n");
  fprintf(file, "ret\n");

  fclose(file);
}