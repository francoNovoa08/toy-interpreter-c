#ifndef CODEGEN_H
#define CODEGEN_H

#include "utils/data_structures/AST.h"

/**
 * @brief Creates a file with x86 assembly for an AST
 *
 * @param tree The AST to generate
 * @param output_path The path for the created file
 */
void codegen(AST_Node *tree, const char *output_path);

#endif // CODEGEN_H