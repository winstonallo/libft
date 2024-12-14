CC = cc
BLOCK_SIZE=$(shell stat -fc %s .)


LIBFT_FLAGS = -L./libft -lft

SRC_DIR = $(PWD)/libft/src
OBJ_DIR = $(PWD)/libft/obj

CFLAGS = -DFS_BLOCK_SIZE=${BLOCK_SIZE} -Wall -Wextra -Werror \
	-I$(PWD)/inc \
	-I$(SRC_DIR)/mem \
	-I$(SRC_DIR)/alloc \
	-I$(SRC_DIR)/print \
	-I$(SRC_DIR)/str \
	-I$(SRC_DIR)/char
		

SRCS =  ${SRC_DIR}/alloc/alloc.c \
		${SRC_DIR}/mem/mem.c \
		${SRC_DIR}/str/str.c \
		${SRC_DIR}/print/print.c \
		${SRC_DIR}/bit/bit.c \
		${SRC_DIR}/char/char.c \

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
