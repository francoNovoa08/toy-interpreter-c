#include "utils/data_structures/symbol_table.h"
#include "utils/data_structures/hashmap.h"

SymbolTable *SymbolTable_create() { return HashMap_create(); }

bool SymbolTable_assign(SymbolTable *table, const char *key, int value) {
  return HashMap_insert(table, key, value);
}

bool SymbolTable_get(SymbolTable *table, const char *key, int *out_value) {
  return HashMap_get(table, key, out_value);
}

void SymbolTable_free(SymbolTable *table) { HashMap_free(table); }