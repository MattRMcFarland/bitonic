# Matt McFarland
# Makefile for bitonic search

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g

# Source directory files

# Source .c files
SRC_FILES = bitonic.c bitonic.h

# Should be SRC_FILES with .o
SRC_OBJS = bitonic.o

# Test files
TEST_FILES = bitonic_test.c

# Test object files
TEST_OBJS = bitonic_test.o

# Test executable
TEST_EXEC = bitonic_test

test: $(TEST_EXEC) 
	./$(TEST_EXEC)

quiet: $(TEST_EXEC)
	./$(TEST_EXEC) > /dev/null

$(TEST_EXEC): $(SRC_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(SRC_OBJS) $(TEST_OBJS) -o $(TEST_EXEC) 

$(SRC_OBJS): $(SRC_FILES)
	$(CC) $(CFLAGS) -c $(SRC_FILES)

clean:
	rm -f $(SRC_OBJS)
	rm -f $(TEST_OBJS)
	rm -f $(TEST_EXEC)
	rm -f *.gch