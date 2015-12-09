# Matt McFarland
# Makefile for bitonic search

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g

# Source directory files
SRC_DIR = src

# Source .c files
SRC_FILES = $(SRC_DIR)/bitonic.c $(SRC_DIR)/bitonic.h

# Should be SRC_FILES with .o
SRC_OBJS = $(SRC_DIR)/bitonic.o

# Test Directory
TEST_DIR = test

# Test files
TEST_FILES = $(TEST_DIR)/bitonic_test.c

# Test object files
TEST_OBJS = $(TEST_DIR)/bitonic_test.o

# Test executable
TEST_EXEC = $(TEST_DIR)/bitonic_test

test: $(TEST_EXEC) 
	./$(TEST_EXEC)

quiet: $(TEST_EXEC)
	./$(TEST_EXEC) > /dev/null

$(TEST_EXEC): $(SRC_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(SRC_OBJS) $(TEST_OBJS) -o $(TEST_EXEC) 

$(SRC_OBJS): $(SRC_FILES)
	$(CC) $(CFLAGS) -c $< -o $(SRC_OBJS)

clean:
	rm -f $(SRC_OBJS)
	rm -f $(TEST_OBJS)
	rm -f $(TEST_EXEC)
	rm -f $(SRC_DIR)/*.gch
