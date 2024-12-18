CC = cc

BLOCK_SIZE=$(shell stat -fc %s .)

CFLAGS = -O3 -DFS_BLOCK_SIZE=${BLOCK_SIZE} -Wall -Wextra -Werror \
	-I./src \
	-I./src/mem \
	-I./src/alloc \
	-I./src/print \
	-I./src/str \
	-I./src/char \
	-I./src/map

SRC_DIR = src
OBJ_DIR = obj

NAME = libft.a

SRCS = $(wildcard $(SRC_DIR)/**/*.c)
HEADERS = $(wildcard $(SRC_DIR)/**/*.h)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
