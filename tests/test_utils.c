#include "parser.h"
#include <stdlib.h>

static ParserState *make_state(Token *tokens, size_t token_count) {
  ParserState *state = malloc(sizeof(ParserState));
  state->tokens = tokens;
  state->token_count = token_count;
  state->pos = 0;

  return state;
}

static ParserState *make_state_from_input(char *input) {
  size_t count;
  Token *tokens = tokenise_string(input, &count);

  return make_state(tokens, count);
}

static void free_state(ParserState *state) {
  free(state->tokens);
  free(state);
}