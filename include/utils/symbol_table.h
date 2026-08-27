#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "utils/data_structures/hashmap.h"
typedef HashMap SymbolTable;

SymbolTable *SymbolTable_create();

bool SymbolTable_assign(SymbolTable *table, const char *key, int value);

bool SymbolTable_get(SymbolTable *table, const char *key, int *out_value);

void SymbolTable_free(SymbolTable *table);

#endif // SYMBOL_TABLE_H