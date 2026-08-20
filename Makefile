CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LIB_SRC = src/token.c src/utils/token_utils.c
TEST_SRC = tests/test_token.c
TARGET = interpreter
TEST_TARGET = test_token

$(TARGET): $(LIB_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(LIB_SRC)

$(TEST_TARGET): $(LIB_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(LIB_SRC) $(TEST_SRC)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: clean test