CC = cc
BLOCK_SIZE=$(shell stat -fc %s .)


LIBFT_FLAGS = -L./libft -lft

SRC_DIR = src
OBJ_DIR = obj

CFLAGS = -O3 -DFS_BLOCK_SIZE=${BLOCK_SIZE} -Wall -Wextra -Werror \
    -I$(PWD)/libft/src \
    -I$(PWD)/libft/src/mem \
    -I$(PWD)/libft/src/alloc \
    -I$(PWD)/libft/src/print \
    -I$(PWD)/libft/src/str \
    -I$(PWD)/libft/src/char
    

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
	echo ${BLOCK_SIZE}
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
