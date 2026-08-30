#include "evaluate.h"
#include "parser.h"
#include "utils/data_structures/symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char buffer[256];
  char result_str[20];
  SymbolTable *table = SymbolTable_create();
  printf("Enter text to interpret.\n");

  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    buffer[strcspn(buffer, "\n")] = 0;

    if (strcmp(buffer, "exit") == 0) {
      break;
    }

    size_t count;
    Token *tokens = tokenise_string(buffer, &count);
    ParserState *state = malloc(sizeof(ParserState));
    state->tokens = tokens;
    state->token_count = count;
    state->pos = 0;

    AST_Node *tree = parse_statement(state);

    if (tree == NULL) {
      printf("%s\n", get_error_message(state->error));
      free(state->tokens);
      free(state);
      continue;
    }

    EvaluationResult result = evaluate(tree, table);

    if (result.error != SUCCESS) {
      printf("%s\n", get_error_message(result.error));
      free(state->tokens);
      free(state);
      continue;
    }

    if (tree->type != NODE_WHILE && tree->type != NODE_IF &&
        tree->type != NODE_STATEMENT_LIST) {
      snprintf(result_str, sizeof(result_str), "%d", result.result);
      printf("%s\n", result_str);
    }

    free(state->tokens);
    free(state);
  }

  free(table);
}