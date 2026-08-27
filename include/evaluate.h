#ifndef EVALUATE_H
#define EVALUATE_H

#include "utils/data_structures/AST.h"
#include "utils/data_structures/symbol_table.h"
#include "utils/errors.h"
typedef struct {
    int result;
    ErrorCode error;
} EvaluationResult;

/**
 * @brief Evaluates a built AST expression
 *
 * @param tree The built AST
 * @param table The symbol table for variables
 *
 * @return The struct containing the result and error message if applicable
 */
EvaluationResult evaluate(AST_Node *tree, SymbolTable *table);

#endif // EVALUATE_H