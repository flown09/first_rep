CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
SRC = graph.c rpn.c infix_to_rpn.c stack.c checks.c
OBJ = graph.o rpn.o infix_to_rpn.o stack.o checks.o
BUILD_DIR = ../build
EXEC = $(BUILD_DIR)/graph

all: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@rm -f $(EXEC)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(OBJ)

rebuild: clean all