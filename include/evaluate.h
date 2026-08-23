#ifndef EVALUATE_H
#define EVALUATE_H

#include "utils/AST.h"
#include "utils/errors.h"
typedef struct {
    int result;
    ErrorCode error;
} EvaluationResult;

/**
 * @brief Evaluates a built AST expression
 *
 * @param tree The built AST
 *
 * @return The struct containing the result and error message if applicable
 */
EvaluationResult evaluate(AST_Node *tree);

#endif // EVALUATE_H