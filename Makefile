CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

LIB_SRC = src/token.c src/utils/token_utils.c src/parser.c src/utils/data_structures/AST.c \
	      src/evaluate.c src/utils/errors.c src/utils/data_structures/hashmap.c

TARGET = interpreter

TEST_TOKEN_SRC = tests/test_token.c
TEST_TOKEN_TARGET = test_token

TEST_PARSER_SRC = tests/test_parser.c
TEST_PARSER_TARGET = test_parser

TEST_EVALUATE_SRC = tests/test_evaluate.c
TEST_EVALUATE_TARGET = test_evaluate

$(TARGET): $(LIB_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(LIB_SRC)

$(TEST_TOKEN_TARGET): $(LIB_SRC) $(TEST_TOKEN_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TOKEN_TARGET) $(LIB_SRC) $(TEST_TOKEN_SRC)

$(TEST_PARSER_TARGET): $(LIB_SRC) $(TEST_PARSER_SRC)
	$(CC) $(CFLAGS) -o $(TEST_PARSER_TARGET) $(LIB_SRC) $(TEST_PARSER_SRC)

$(TEST_EVALUATE_TARGET): $(LIB_SRC) $(TEST_EVALUATE_SRC)
	$(CC) $(CFLAGS) -o $(TEST_EVALUATE_TARGET) $(LIB_SRC) $(TEST_EVALUATE_SRC)

test-token: $(TEST_TOKEN_TARGET)
	./$(TEST_TOKEN_TARGET)

test-parser: $(TEST_PARSER_TARGET)
	./$(TEST_PARSER_TARGET)

test-evaluate: $(TEST_EVALUATE_TARGET)
	./$(TEST_EVALUATE_TARGET)

test: test-token test-parser test-evaluate

clean:
	rm -f $(TARGET) $(TEST_TOKEN_TARGET) $(TEST_PARSER_TARGET) $(TEST_EVALUATE_TARGET)

.PHONY: clean test test-token test-parser test-evaluate