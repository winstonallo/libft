CC = cc
BLOCK_SIZE=$(shell stat -fc %s .)


LIBFT_FLAGS = -L./libft -lft

SRC_DIR = $(PWD)/libft/src
OBJ_DIR = $(PWD)/libft/obj

CFLAGS = -O3 -DFS_BLOCK_SIZE=${BLOCK_SIZE} -Wall -Wextra -Werror \
	-I./src \
	-I./src/mem \
	-I./src/alloc \
	-I./src/print \
	-I./src/str \
	-I./src/char \
	-I./src/map


SRCS =  ./src/alloc/alloc.c \
		./src/mem/mem.c \
		./src/str/str.c \
		./src/print/print.c \
		./src/bit/bit.c \
		./src/char/char.c \
		./src/map/map.c \

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = libft.a

.PHONY: all clean fclean re b

all: $(OBJ_DIR) $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
