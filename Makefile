CC = cc
BLOCK_SIZE=$(shell stat -fc %s .)

CFLAGS = -DFS_BLOCK_SIZE=${BLOCK_SIZE} -Wall -Wextra -Werror -Isrc/alloc -Isrc/mem -Isrc/print -Isrc/str -Isrc/char -g

LIBFT_FLAGS = -L./libft -lft

SRC_DIR = src
OBJ_DIR = obj


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
	echo 
	echo 
	echo 
	echo 
	echo 
	echo ${BLOCK_SIZE}

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
