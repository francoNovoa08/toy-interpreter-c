#ifndef ANALYSE_H
#define ANALYSE_H

#include "utils/data_structures/AST.h"
#include "utils/data_structures/hashmap.h"
#include "utils/errors.h"

typedef struct {
    ErrorCode error;
    char *variable;
} AnalysisResult;

/**
 * @brief Analyses a built AST expression
 *
 * @param tree The built AST
 * @param set A Hashmap to check for the use of unassigned variables
 *
 * @return The struct containing an error and variable causing it if applicable
 */
AnalysisResult analyse(AST_Node *tree, HashMap *set);

#endif // ANALYSE_H