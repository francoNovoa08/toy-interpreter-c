CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

LIB_SRC = src/token.c src/utils/token_utils.c src/parser.c src/utils/data_structures/AST.c \
	      src/evaluate.c src/utils/errors.c src/utils/data_structures/hashmap.c \
		  src/utils/evaluate_utils.c src/utils/data_structures/symbol_table.c \
		  src/utils/parser_utils.c src/analyse.c src/utils/data_structures/vector.c \
		  src/codegen.c

MAIN_SRC = src/main.c

TARGET = interpreter

TEST_TOKEN_SRC = tests/test_token.c
TEST_TOKEN_TARGET = test_token

TEST_PARSER_SRC = tests/test_parser.c
TEST_PARSER_TARGET = test_parser

TEST_EVALUATE_SRC = tests/test_evaluate.c
TEST_EVALUATE_TARGET = test_evaluate

TEST_ANALYSE_SRC = tests/test_analyse.c
TEST_ANALYSE_TARGET = test_analyse

TEST_CODEGEN_SRC = tests/test_codegen.c
TEST_CODEGEN_TARGET = test_codegen

$(TARGET): $(LIB_SRC) $(MAIN_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(LIB_SRC) $(MAIN_SRC)

$(TEST_TOKEN_TARGET): $(LIB_SRC) $(TEST_TOKEN_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TOKEN_TARGET) $(LIB_SRC) $(TEST_TOKEN_SRC)

$(TEST_PARSER_TARGET): $(LIB_SRC) $(TEST_PARSER_SRC)
	$(CC) $(CFLAGS) -o $(TEST_PARSER_TARGET) $(LIB_SRC) $(TEST_PARSER_SRC)

$(TEST_EVALUATE_TARGET): $(LIB_SRC) $(TEST_EVALUATE_SRC)
	$(CC) $(CFLAGS) -o $(TEST_EVALUATE_TARGET) $(LIB_SRC) $(TEST_EVALUATE_SRC)

$(TEST_ANALYSE_TARGET): $(LIB_SRC) $(TEST_ANALYSE_SRC)
	$(CC) $(CFLAGS) -o $(TEST_ANALYSE_TARGET) $(LIB_SRC) $(TEST_ANALYSE_SRC)

$(TEST_CODEGEN_TARGET): $(LIB_SRC) $(TEST_CODEGEN_SRC)
	$(CC) $(CFLAGS) -o $(TEST_CODEGEN_TARGET) $(LIB_SRC) $(TEST_CODEGEN_SRC)

test-token: $(TEST_TOKEN_TARGET)
	./$(TEST_TOKEN_TARGET)

test-parser: $(TEST_PARSER_TARGET)
	./$(TEST_PARSER_TARGET)

test-evaluate: $(TEST_EVALUATE_TARGET)
	./$(TEST_EVALUATE_TARGET)

test-analyse: $(TEST_ANALYSE_TARGET)
	./$(TEST_ANALYSE_TARGET)

test-codegen: $(TEST_CODEGEN_TARGET)
	./$(TEST_CODEGEN_TARGET)	

test: test-token test-parser test-evaluate test-analyse test-codegen

clean:
	rm -f $(TARGET) $(TEST_TOKEN_TARGET) $(TEST_PARSER_TARGET) \
	$(TEST_EVALUATE_TARGET) $(TEST_ANALYSE_TARGET) $(TEST_CODEGEN_TARGET)

.PHONY: clean test test-token test-parser test-evaluate test-analyse test-codegen