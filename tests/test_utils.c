#include "parser.h"
#include <stdio.h>
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

static char* read_assembly_file(const char* filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    return NULL;
  }

   if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }

    long length = ftell(file);
    if (length < 0) {
        fclose(file);
        return NULL;
    }

    rewind(file);

    char* buffer = (char*)malloc((size_t)length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    size_t read_bytes = fread(buffer, 1, (size_t)length, file);
    if (read_bytes != (size_t)length) {
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[length] = '\0';

    fclose(file);
    return buffer;
}