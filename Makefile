CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

LIB_SRC = src/token.c src/utils/token_utils.c src/parser.c src/utils/AST.c

TARGET = interpreter

TEST_TOKEN_SRC = tests/test_token.c
TEST_TOKEN_TARGET = test_token

TEST_PARSER_SRC = tests/test_parser.c
TEST_PARSER_TARGET = test_parser

$(TARGET): $(LIB_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(LIB_SRC)

$(TEST_TOKEN_TARGET): $(LIB_SRC) $(TEST_TOKEN_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TOKEN_TARGET) $(LIB_SRC) $(TEST_TOKEN_SRC)

$(TEST_PARSER_TARGET): $(LIB_SRC) $(TEST_PARSER_SRC)
	$(CC) $(CFLAGS) -o $(TEST_PARSER_TARGET) $(LIB_SRC) $(TEST_PARSER_SRC)

test-token: $(TEST_TOKEN_TARGET)
	./$(TEST_TOKEN_TARGET)

test-parser: $(TEST_PARSER_TARGET)
	./$(TEST_PARSER_TARGET)

test: test-token test-parser

clean:
	rm -f $(TARGET) $(TEST_TOKEN_TARGET) $(TEST_PARSER_TARGET)

.PHONY: clean test test-token test-parser