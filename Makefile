CC = cc

BLOCK_SIZE=$(shell stat -fc %s .)

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
TESTS_DIR = tests

CFLAGS = -DFS_BLOCK_SIZE=${BLOCK_SIZE} -Wall -Wextra -Werror -I$(INC_DIR) -mavx2 -march=native -mtune=native -g

NAME = libft.a
TEST_NAME = libft_test

TESTS_SRCS = $(shell find $(TESTS_DIR) -name "*.c")
SRCS = $(shell find $(SRC_DIR) -name "*.c")
HEADERS = $(wildcard $(INC_DIR)/**/*.h)
TESTS_OBJS = $(patsubst $(TESTS_DIR)/%.c, $(OBJ_DIR)/tests/%.o, $(TESTS_SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: $(TESTS_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

test: $(NAME) $(TESTS_OBJS)
	$(CC) $(CFLAGS) -g $(TESTS_OBJS) -L. -lft -o $(TEST_NAME)
	valgrind ./$(TEST_NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all
